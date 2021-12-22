
#include "Puzzle.h"

int max(int a, int b){
	return a > b ? a : b;
}

int min(int a, int b){
	return a > b? b : a;
}

Puzzle::Puzzle(){
	
	grid = NULL;
	solvedGrid = NULL;

	picture = NULL;
	hoverPieceSurface = NULL;

	dimensao = 0;

	pictureX = 0;
	pictureY = 0;
	pictureSize = 0;
	pieceSize = 0;

	pSelected.linha = 0;
	pSelected.coluna = 0;

	hasSelected = false;
	isMouseHovering = false;
	hintMode = false;

	moves = 0;
}

bool Puzzle::init(){

	centerXY();

	SDL_Surface* hoverTemp = NULL;

	hoverTemp = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, pieceSize, pieceSize, COLOR_DEPTH, 0,0,0,0);

	if(!hoverTemp)
		return false;
	
	hoverPieceSurface = SDL_DisplayFormat(hoverTemp);

	SDL_FillRect(hoverPieceSurface, NULL, SDL_MapRGB(hoverPieceSurface->format,210,210,210));

	SDL_SetAlpha(hoverPieceSurface, SDL_SRCALPHA|SDL_RLEACCEL, HOVER_PIECE_ALPHA);

	SDL_FreeSurface(hoverTemp);

	if(!initTexts())
		return false;

	if(!hintButton.init("images/game/bgBotao.png",669,60))
		return false;
	hintButton.setBlended(true);
	hintButton.setText("Hint");

	return true;
}

bool Puzzle::initTexts(){

	int distancia = pictureX - GRID_BORDER;
	char str[5];

	if(!gameTitleText.onLoad("fonts/Polo Brush.ttf",32))
		return false;
	gameTitleText.setBlended(true);
	gameTitleText.setText("Picture Puzzle");
	gameTitleText.center(0,WND_WIDTH);
	gameTitleText.y = -3;

	if(!movesText.onLoad("fonts/Polo Brush.ttf",26))
		return false;
	movesText.setBlended(true);
	movesText.setText("Moves");
	movesText.center(0, pictureX - GRID_BORDER);
	movesText.y = 60;

	if(!movesQtText.onLoad("fonts/Polo Brush.ttf",24))
		return false;
	movesQtText.setBlended(true);
	sprintf_s(str,"%d",moves);
	movesQtText.setText(str);
	movesQtText.center(0, pictureX - GRID_BORDER);
	movesQtText.y = 85;

	if(!timeText.onLoad("fonts/Polo Brush.ttf", 26))
		return false;
	timeText.setBlended(true);
	timeText.setText("Time");
	timeText.center(0, pictureX - GRID_BORDER);
	timeText.y = 140;

	//Chronometer
	if(!time.init())
		return false;
	time.setBlended(true);
	time.setTime(0,0,0);
	time.center(0, pictureX - GRID_BORDER);
	time.y = 165;
	time.start();

	if(!correctText.onLoad("fonts/Polo Brush.ttf",26))
		return false;
	correctText.setBlended(true);
	correctText.setText("Correct");
	correctText.center(0, pictureX - GRID_BORDER);
	correctText.y = 220;

	if(!correctQtText.onLoad("fonts/Polo Brush.ttf",26))
		return false;
	correctQtText.setBlended(true);
	sprintf_s(str,"%d",checkCorretas());
	correctQtText.setText(str);
	correctQtText.center(0, pictureX - GRID_BORDER);
	correctQtText.y = 245;
	
	return true;
}

void Puzzle::loop(){

	time.loop();
}

void Puzzle::render(SDL_Surface* destSurface){

	SDL_FillRect(destSurface, &pictureRect, SDL_MapRGB(destSurface->format,0,0,0));

	gameTitleText.onRender(destSurface);
	movesText.onRender(destSurface);
	movesQtText.onRender(destSurface);
	timeText.onRender(destSurface);
	time.render(destSurface);
	correctText.onRender(destSurface);
	correctQtText.onRender(destSurface);

	hintButton.render(destSurface);

	if(hasSelected)
		SDL_FillRect(destSurface, &pieceSelectedRect, SDL_MapRGB(destSurface->format,255,255,255));

	for(int i=0; i<dimensao; i++)
		for(int j=0; j<dimensao; j++)
			if(hintMode)
				drawPiece(destSurface, solvedGrid[i][j], i, j);
			else
				drawPiece(destSurface, grid[i][j], i, j);

	if(isMouseHovering)
		CSurface::OnDraw(destSurface, hoverPieceSurface, hoverX, hoverY);
}

void Puzzle::deletaGrid(int** grid){
	
	for(int i=0; i<dimensao; i++)
		delete[] grid[i];

	delete[] grid;

	grid = NULL;
}

int** Puzzle::alocaGrid(){

	int** temp = NULL;

	if(dimensao <= 0)
		return false;

	temp = new int*[dimensao];

	for(int i=0; i<dimensao; i++)
		temp[i] = new int[dimensao];

	int k = 1;
	for(int i=0; i<dimensao; i++)
		for(int j=0; j<dimensao; j++)
		{
			temp[i][j] = k;
			k++;
		}

	return temp;
}

void Puzzle::cleanup(){

	deletaGrid(grid);
	deletaGrid(solvedGrid);

	if(picture)
		SDL_FreeSurface(picture);

	if(hoverPieceSurface)
		SDL_FreeSurface(hoverPieceSurface);

	picture = NULL;
	hoverPieceSurface = NULL;

	gameTitleText.onCleanup();
	movesText.onCleanup();
	movesQtText.onCleanup();
	timeText.onCleanup();
	time.cleanup();
	correctText.onCleanup();
	correctQtText.onCleanup();

	hintButton.onCleanup();
}

bool Puzzle::setDimensao(int d){

	if(d <= 0)
		return false;

	if(grid)
		deletaGrid(grid);

	if(solvedGrid)
		deletaGrid(solvedGrid);

	dimensao = d;

	//imagem 1:1
	pieceSize = pictureSize / dimensao;

	if((grid = alocaGrid()) == NULL)
		return false;

	if((solvedGrid = alocaGrid()) == NULL)
		return false;

	return true;
}

bool Puzzle::load(char *file){

	int resizedSize = pictureSize;

	if(pictureSize <= 0)
		return false;
	
	SDL_Surface *image_org = NULL, *image = NULL, *cropImage = NULL, *cropImageConv = NULL, *finalImage = NULL;
	double factorX = 1, factorY = 1;

	if((image_org = CSurface::OnLoad(file)) == NULL)
		return false;

	if(image_org->w > IMAGE_RESIZE_W)
		factorX = (double)IMAGE_RESIZE_W/image_org->w;

	if(image_org->h > IMAGE_RESIZE_H)
		factorY = (double)IMAGE_RESIZE_H/image_org->h;

	image = rotozoomSurfaceXY(image_org, 0, factorX, factorY, SMOOTHING_ON);

	if(image->w <= pictureSize && image->h <= pictureSize)
		resizedSize = min(image->w, image->h);

	cropImage = SDL_CreateRGBSurface(SDL_SWSURFACE, resizedSize, resizedSize, COLOR_DEPTH,
									image_org->format->Rmask, image_org->format->Gmask, 
									image_org->format->Bmask, image_org->format->Amask);

	cropImageConv = SDL_DisplayFormat(cropImage);

	SDL_Rect cropRect;

	if(image->w > resizedSize)
		cropRect.x = image->w / 2 - resizedSize / 2;
	else
		cropRect.x = 0;

	if(image->h > resizedSize)
		cropRect.y = image->h / 2 - resizedSize / 2;
	else
		cropRect.y = 0;

	cropRect.w = resizedSize;
	cropRect.h = resizedSize;

	if(SDL_BlitSurface(image, &cropRect, cropImageConv, NULL) < 0)
		return false;

	finalImage = rotozoomSurface(cropImageConv, 0, (double) pictureSize / resizedSize, SMOOTHING_ON);

	picture = SDL_DisplayFormat(finalImage);

	SDL_FreeSurface(image_org);
	SDL_FreeSurface(image);
	SDL_FreeSurface(cropImage);
	SDL_FreeSurface(cropImageConv);
	SDL_FreeSurface(finalImage);

	if(!picture)
		return false;

	return true;
}

void Puzzle::drawPiece(SDL_Surface* destSurface, int p, int linha, int coluna){
	
	if(!destSurface)
		return;

	PecaPos pos = getSolutionPecaPos(p);

	CSurface::OnDraw(destSurface, picture, 
					pictureX + coluna * (pieceSize + GRID_SPACING), 
					pictureY + linha * (pieceSize + GRID_SPACING),
					pos.coluna * pieceSize,
					pos.linha * pieceSize,
					pieceSize,
					pieceSize);

}

void Puzzle::setPictureSize(int s){
	if(s > 0)
		pictureSize = s;
}

int Puzzle::getPictureX(){
	return pictureX;
}

int Puzzle::getPictureY(){
	return pictureY;
}

void Puzzle::setPictureX(int x){
	if(x >= 0)
		pictureX = x;
}

void Puzzle::setPictureY(int y){
	if(y >= 0)
		pictureY = y;
}

int Puzzle::getPictureSize(){
	return pictureSize;
}

void Puzzle::centerX(){
	pictureX = WND_WIDTH / 2 - (pictureSize + (dimensao-1) * GRID_SPACING) / 2;

	pictureRect.x = pictureX - GRID_BORDER;
	pictureRect.y = pictureY - GRID_BORDER;
	pictureRect.w = dimensao * pieceSize + (dimensao - 1) * GRID_SPACING + 2 * GRID_BORDER;
	pictureRect.h = dimensao * pieceSize + (dimensao - 1) * GRID_SPACING + 2 * GRID_BORDER;
}

void Puzzle::centerY(){
	pictureY = WND_HEIGHT / 2 - (pictureSize + (dimensao-1) * GRID_SPACING) / 2;

	pictureRect.x = pictureX - GRID_BORDER;
	pictureRect.y = pictureY - GRID_BORDER;
	pictureRect.w = dimensao * pieceSize + (dimensao - 1) * GRID_SPACING + 2 * GRID_BORDER;
	pictureRect.h = dimensao * pieceSize + (dimensao - 1) * GRID_SPACING + 2 * GRID_BORDER;
}

void Puzzle::centerXY(){
	centerX();
	centerY();
}

PecaPos Puzzle::getSolutionPecaPos(int p){
	
	PecaPos r;

	r.linha = -1;
	r.coluna = -1;

	if(p < 0 || p > dimensao*dimensao)
		return r;

	if(p % dimensao != 0)
	{
		r.linha = p / dimensao;
		r.coluna = p % dimensao - 1;
	}
	else
	{
		r.linha = p / dimensao - 1;
		r.coluna = dimensao - 1; 
	}

	return r;
}

int Puzzle::getPeca(PecaPos pos){
	
	if(pos.linha >= 0 && pos.coluna >= 0)
		return grid[pos.linha][pos.coluna];
	else
		return -1;
}

void Puzzle::swapElements(PecaPos pos1, PecaPos pos2){

	if(pos1.linha < 0 || pos1.coluna < 0 ||
		pos2.linha < 0 || pos2.coluna < 0)
		return;

	if(pos1.linha == pos2.linha && pos1.coluna == pos2.coluna)
		return;

	//TODO: fazer em assembly
	grid[pos1.linha][pos1.coluna] = grid[pos1.linha][pos1.coluna] ^ grid[pos2.linha][pos2.coluna];
	grid[pos2.linha][pos2.coluna] = grid[pos1.linha][pos1.coluna] ^ grid[pos2.linha][pos2.coluna];
	grid[pos1.linha][pos1.coluna] = grid[pos1.linha][pos1.coluna] ^ grid[pos2.linha][pos2.coluna];
}

void Puzzle::embaralhar(){
	
	PecaPos r1, r2;

	for(int i=0; i< 20*dimensao*dimensao; i++)
	{
		r1.linha = rand() % dimensao;
		r1.coluna = rand() % dimensao;
		r2.linha = rand() % dimensao;
		r2.coluna = rand() % dimensao;
		
		swapElements(r1,r2);
	}

	char str[5];
	sprintf_s(str,"%d",checkCorretas());
	correctQtText.setText(str);
	correctQtText.center(0, pictureX - GRID_BORDER);
}

void Puzzle::resolver(int** grid){
	int k = 1;
	
	for(int i=0; i<dimensao; i++)
		for(int j=0; j<dimensao; j++)
		{
			grid[i][j] = k;
			k++;
		}
}

PecaPos Puzzle::getSelected(){
	return pSelected;
}

void Puzzle::LMouseDown(int mx, int my){
	
	int linha, coluna;
	char str[5];

	linha = (my - pictureY) / (pieceSize + GRID_SPACING);
	coluna = (mx - pictureX) / (pieceSize + GRID_SPACING);

	if(!hasSelected)
	{
		//linha e coluna determinam a peça selecionada
		pSelected.linha = linha;
		pSelected.coluna = coluna;

		hasSelected = true;
	}
	else
	{
		//Clicou na peça selecionada?
		if(pSelected.linha == linha && pSelected.coluna == coluna)
			hasSelected = false;
		else
		{
			//linha e coluna determinam a peça a ser trocada
			PecaPos pos;
			pos.linha = linha;
			pos.coluna = coluna;

			swapElements(pos,pSelected);
			moves++;
		
			sprintf_s(str, "%d", moves);
			movesQtText.setText(str);
			movesQtText.center(0, pictureX - GRID_BORDER);

			sprintf_s(str,"%d",checkCorretas());
			correctQtText.setText(str);
			correctQtText.center(0, pictureX - GRID_BORDER);

			hasSelected = false;
		}
	}

	if(hasSelected)
	{
		pieceSelectedRect.x = pictureX + coluna * pieceSize + (coluna - 1) * GRID_SPACING;
		pieceSelectedRect.y = pictureY + linha * pieceSize + (linha - 1) * GRID_SPACING;
		pieceSelectedRect.w = pieceSize + 2 * GRID_SPACING;
		pieceSelectedRect.h = pieceSize + 2 * GRID_SPACING;
	}
}

void Puzzle::mouseHover(int posX, int posY){

	if( posX < pictureX || posX > pictureX + dimensao * pieceSize + (dimensao-1)*GRID_SPACING ||
	    posY < pictureY || posY > pictureY + dimensao * pieceSize + (dimensao-1)*GRID_SPACING )
	{
		isMouseHovering = false;
		return;
	}

	int linha, coluna;

	linha = (posY - pictureY) / (pieceSize + GRID_SPACING);
	coluna = (posX - pictureX) / (pieceSize + GRID_SPACING);

	hoverX = pictureX + coluna * pieceSize + coluna * GRID_SPACING; 
	hoverY = pictureY + linha * pieceSize + linha * GRID_SPACING;

	isMouseHovering = true;
}

int Puzzle::checkCorretas(){
	
	int corretas = 0;
	int k = 1;

	for(int i=0; i<dimensao; i++)
		for(int j=0; j<dimensao; j++)
		{
			if(grid[i][j] == k)
				corretas++;

			k++;
		}

	return corretas;
}

void Puzzle::setHintMode(bool h){
	hintMode = h;

	if(hintMode)
		hasSelected = false;
}