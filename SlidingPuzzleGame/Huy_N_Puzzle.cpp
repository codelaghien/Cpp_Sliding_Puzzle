#include "Huy_N_Puzzle.h"

Huy_N_Puzzle::Huy_N_Puzzle(int size) {
	/* initialize random seed: */
	srand(time(NULL));

	_Size = size;
	HuySize consoleSize = HuyCurrentConsole::getSize();
	_HuyWindows = HuyWindows(0, 0, consoleSize.width, consoleSize.height, 1, HuyColors::BLUE, HuyColors::WHITE);
	_HuyWindows.showConsoleCursor(false);
	_HuyWindows.clearConsole();
	_HuyWindows.drawFrame();

	wstring title = L" 15-puzzle ";
	_HuyWindows.write(title, (consoleSize.width - title.length()) / 2, 0, HuyColors::RED, HuyColors::WHITE);

	_EmptyPosition.X = _Size - 1;
	_EmptyPosition.Y = _Size - 1;
	initBoard();

	printBottomCommands();
}

void Huy_N_Puzzle::run() {
	drawBoard();

	unsigned int x = _getch();
	while (x != 120) { // x
		switch (x)
		{
			case 114: // r
				randomBoard();
				break;
			case 75: // left
				doMove(Direction::LEFT);
				break;
			case 77: // right
				doMove(Direction::RIGHT);
				break;
			case 72: // up
				doMove(Direction::UP);
				break;
			case 80: // down
				doMove(Direction::DOWN);
				break;
			default:
				break;
		}
		x = _getch();
	}

	bye();
}
void Huy_N_Puzzle::intro() {
	int w = _HuyWindows.getWidth() - 20;
	if (w > 80) w = 80;
	if (w < 80) w = _HuyWindows.getWidth() - 2;
	int h = 29;
	int x = (_HuyWindows.getWidth() - w) / 2;
	int y = (_HuyWindows.getHeight() - h) / 2;

	_HuyWindows.saveScreenRect(x, y, w, h);

	wstring title = L" Giới thiệu tổng quát ";
	int background = HuyColors::LIGHTBLUE;
	int foreground = HuyColors::WHITE;

	_HuyWindows.animateFrame(x, y, w, h, background, foreground);

	HuyWindows introWin(x, y, w, h, 0, background, foreground);
	introWin.clearConsole();
	introWin.drawFrame();
	introWin.write(title, (w - title.length()) / 2, 0, HuyColors::BROWN, foreground);

	foreground = HuyColors::WHITE;
	int row = 3;
	int col = 4;
	wstring sokoban;
	sokoban = L"   _  _____                                    _          ";
	col = (w - sokoban.length()) / 2;
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L" /' )(  ___)                                  (_ )        ";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"(_, || (__   ______  _ _    _   _  ____  ____  | |    __  ";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"  | ||___ `\\(______)( '_`\\ ( ) ( )(_  ,)(_  ,) | |  /'__`\\";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"  | |( )_) |        | (_) )| (_) | /'/_  /'/_  | | (  ___/";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"  (_)`\\___/'        | ,__/'`\\___/'(____)(____)(___)`\\____)";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"                    | |                                   ";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"                    (_)                                   ";
	introWin.write(sokoban, col, row++, background, foreground);

	foreground = HuyColors::WHITE;
	row++;
	col = 4;
	introWin.write(L"Đây là chương trình chơi trò xếp hình đơn giản.", col, row++, background, foreground);
	introWin.write(L"Chương trình được viết bằng ngôn ngữ C++.", col, row++, background, foreground);
	row++;
	introWin.write(L"Đây là trò chơi được sáng chế bởi Noyes Chapman năm 1880.", col, row++, background, foreground);
	introWin.write(L"Ý tưởng của trò chơi là đẩy mấy khung có số vào vị trí 1, 2, 3, 4, ...", col, row++, background, foreground);
	row++;
	introWin.write(L"Những thư viện cần để viết là:", col, row++, background, foreground); 
	introWin.write(L"+ HuyWindows:        tự viết đơn giản - vẽ khung, ...", col, row++, background, foreground);
	introWin.write(L"+ Huy_N_Puzzle:      tự viết đơn giản - bộ máy chính", col, row++, background, foreground);
	introWin.write(L"+ ...", col, row++, background, foreground);
	row += 2;
	sokoban = L"Tác giả: Huy Nguyễn";
	introWin.write(sokoban, (w - sokoban.length()) / 2, row++, background, foreground);
	sokoban = L"Năm 2020";
	introWin.write(sokoban, (w - sokoban.length()) / 2, row++, background, foreground);

	wstring close = L" Nhấn phím bất kỳ để đóng ";
	introWin.write(close, (w - close.length()) / 2, h - 1, background, foreground);

	int c = _getch() - 48;
	_HuyWindows.restoreScreenRect();
}
void Huy_N_Puzzle::printBottomCommands() {
	// http://xahlee.info/comp/unicode_arrows.html
	int col = 1;
	int row = _HuyWindows.getHeight() - 1;
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	wstring temp = L" ← ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size(); 
	 
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	temp = L" ↑ ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size(); 
	 
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	temp = L" ↓ ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size(); 
	 
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	temp = L" → ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size(); // ↔ ↕

	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	temp = L" r ";
	_HuyWindows.write(temp, col, row, HuyColors::BROWN, HuyColors::WHITE);
	col += temp.size();
	temp = L" Xáo trộn "; 
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);
	col += temp.size();
	 
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	temp = L" x ";
	_HuyWindows.write(temp, col, row, HuyColors::RED, HuyColors::WHITE);
	col += temp.size();
	temp = L" Thoát ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);
}
void Huy_N_Puzzle::bye() {
	int row = (_HuyWindows.getHeight() - 8) / 2;
	_HuyWindows.clearConsole();
	wstring byebye = L"";
	byebye = L"██████╗ ██╗   ██╗███████╗      ██████╗ ██╗   ██╗███████╗";
	int col = (_HuyWindows.getWidth() - byebye.size()) / 2;
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██╔══██╗╚██╗ ██╔╝██╔════╝      ██╔══██╗╚██╗ ██╔╝██╔════╝";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██████╔╝ ╚████╔╝ █████╗        ██████╔╝ ╚████╔╝ █████╗";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██╔══██╗  ╚██╔╝  ██╔══╝        ██╔══██╗  ╚██╔╝  ██╔══╝";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██████╔╝   ██║   ███████╗      ██████╔╝   ██║   ███████╗";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"╚═════╝    ╚═╝   ╚══════╝      ╚═════╝    ╚═╝   ╚══════╝";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	for (int i = 0; i < 5; i++) {
		wstring temp = L" Tự động thoát trong " + to_wstring(5 - i) + L" giây ";
		_HuyWindows.write(temp, (_HuyWindows.getWidth() - temp.size()) / 2, _HuyWindows.getHeight() - 3, HuyColors::LIGHTMAGENTA, HuyColors::WHITE);
		Sleep(1000);
	}
}
void Huy_N_Puzzle::randomBoard() { 
	int moves = 0;
	for (int i = 0; i < 10000; i++) {
		int dir = rand() % 4;
		bool moved = false;
		switch (dir)
		{
			case 0:
				moved = doMove(Direction::UP, true);
				break;
			case 1:
				moved = doMove(Direction::RIGHT, true);
				break;
			case 2:
				moved = doMove(Direction::DOWN, true);
				break;
			case 3:
				moved = doMove(Direction::LEFT, true);
				break;
			default:
				break;
		}
		moves += moved ? 1 : 0;
		if (moves > 200) break;
		if (moved) Sleep(30);
	}
	_Count = 0;
}
void Huy_N_Puzzle::drawBlock(int value, int row, int col) {
	int color = (value > 0) ? HuyColors::BROWN : HuyColors::BLUE;
	if (_Board[row][col] == col + (row * _Size) + 1) color = HuyColors::GREEN;

	HuyWindows cell(_Position.X + (_Width * col) + 1, _Position.Y + (_Height * row) + 1, _Width, _Height, 0, color, HuyColors::WHITE);
	cell.showConsoleCursor(false);
	if (value > 0) {
		cell.clearConsole();
		cell.drawFrame(); 
		cell.write(HuyWindows::toWString(value), _Width / 2, _Height / 2);
	}
	else {
		cell.clearConsole(' ', false);
	} 
}
void Huy_N_Puzzle::initBoard() {
	for (int row = 0; row < _Size; row++) {
		for (int col = 0; col < _Size; col++) {
			if (!(row == _EmptyPosition.Y && col == _EmptyPosition.X)) {
				_Board[row][col] = col + (row * _Size) + 1;
			}
			else {
				_Board[row][col] = 0;
			}
		}
	}
}
void Huy_N_Puzzle::drawBoard() {
	_Position.X = (_HuyWindows.getWidth() - (_Width * _Size + 2)) / 2;
	_Position.Y = (_HuyWindows.getHeight() - (_Height * _Size + 2)) / 2;
	HuyWindows frame(_Position.X, _Position.Y, _Width * _Size + 2, _Height * _Size + 2, 1, HuyColors::BLUE, HuyColors::WHITE);
	frame.showConsoleCursor(false);
	frame.clearConsole();
	frame.drawFrame();

	for (int row = 0; row < _Size; row++) {
		for (int col = 0; col < _Size; col++) {
			if (_Board[row][col] != 0) {
				drawBlock(_Board[row][col], row, col);
			} 
		}
	}
}
bool Huy_N_Puzzle::doMove(Direction direction, bool random) {
	bool moved = false;
	switch (direction)
	{
		case Direction::UP:
			if (_EmptyPosition.Y < _Size - 1) {
				HuyPoint from(_EmptyPosition.X, _EmptyPosition.Y + 1);
				move(from, _EmptyPosition);
				moved = true;
			}
			break;
		case Direction::RIGHT:
			if (_EmptyPosition.X > 0) {
				HuyPoint from(_EmptyPosition.X - 1, _EmptyPosition.Y);
				move(from, _EmptyPosition);
				moved = true;
			}
			break;
		case Direction::DOWN:
			if (_EmptyPosition.Y > 0) {
				HuyPoint from(_EmptyPosition.X, _EmptyPosition.Y - 1);
				move(from, _EmptyPosition);
				moved = true;
			}
			break;
		case Direction::LEFT:
			if (_EmptyPosition.X < _Size - 1) {
				HuyPoint from(_EmptyPosition.X + 1, _EmptyPosition.Y);
				move(from, _EmptyPosition);
				moved = true;
			}
			break;
		default:
			break;
	}  
	if (moved && !random) {
		_Count++;
		if (isSolved()) congratulations();
	}
	return moved;
}
void Huy_N_Puzzle::move(HuyPoint fromPosition, HuyPoint toPostion) { 
	_Board[toPostion.Y][toPostion.X] = _Board[fromPosition.Y][fromPosition.X];
	_Board[fromPosition.Y][fromPosition.X] = 0;
	_EmptyPosition = fromPosition;
	drawBlock(_Board[toPostion.Y][toPostion.X], toPostion.Y, toPostion.X);
	drawBlock(_Board[fromPosition.Y][fromPosition.X], fromPosition.Y, fromPosition.X);
}
bool Huy_N_Puzzle::isSolved() { 
	for (int row = 0; row < _Size; row++) {
		for (int col = 0; col < _Size; col++) {
			if (!(row == _EmptyPosition.Y && col == _EmptyPosition.X)) {
				if (_Board[row][col] != col + (row * _Size) + 1) return false;
			} 
		}
	}
	return true;
}
void Huy_N_Puzzle::alert(wstring title, wstring messages[], int size, bool info, string position, int closeTime) {
	int w = 50;
	int h = size + 4;
	int x = (_HuyWindows.getWidth() - w) / 2;
	int y = position == "bottom" ? _HuyWindows.getHeight() - h - 2 : (_HuyWindows.getHeight() - h) / 2;

	_HuyWindows.saveScreenRect(x, y, w, h);

	int background = info ? HuyColors::LIGHTMAGENTA : HuyColors::RED;
	int foreground = HuyColors::WHITE;

	_HuyWindows.animateFrame(x, y, w, h, background, foreground);

	HuyWindows infoWin(x, y, w, h, 0, background, foreground);
	infoWin.clearConsole();
	infoWin.drawFrame();
	infoWin.write(title, (w - title.length()) / 2, 0, HuyColors::BLUE, foreground);

	for (int i = 0; i < size; i++) {
		infoWin.write(messages[i], (w - messages[i].length()) / 2, 2 + i, background, foreground);
	}

	wstring temp = L"";
	for (int i = closeTime; i > 0; i--) {
		temp = L" Đóng trong " + to_wstring(i) + L" giây ";
		infoWin.write(temp, (w - temp.length()) / 2, h - 1, HuyColors::BLUE, foreground);
		Sleep(1000);
	}

	_HuyWindows.restoreScreenRect();
}
void Huy_N_Puzzle::congratulations() {
	wstring messages[] = { L"Bạn đã giải xong trong " + HuyWindows::toWString(_Count) + L" bước !", L"Bạn là siêu nhân !" };
	alert(L" Wow, chúc mừng bạn ! ", messages, 2, true, "center", 9);
}
