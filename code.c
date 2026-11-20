#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int category(int x) {
	int c = 0;
	while (x > 0) {
		x = x / 10;
		c++;
	}
	return c;
} //подсчет числа разрядов. нужна, чтобы таблица не съезжала



void print_b(int m, int n, int maxm, int maxn, char** board) {
	printf("%*s %s", 1 + maxm, " ", "| ");
	for (int i = 1; i < (n + 1); i++) {
		int min = category(i);
		printf("%d %*s %s", i, maxn - min + 1, " ", "| ");
	}
	printf("%s", "\n");

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0) {
				printf("%d", i + 1);
				int min = category(i + 1);
				printf("%*s %s", maxm + 1 - min, " ", "| ");
			}
			printf("%c %*s %s", board[i][j], maxn, " ", "| ");
			if (j == (n - 1)) { printf("%s", "\n"); }
		}
	}
} //вывод таблицы



int check(int m, int n, int l, char** board, char sym) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j <= n - l; j++) {
			int win = 1;
			for (int k = 0; k < l; k++) {
				if (board[i][j + k] != sym) { win = 0; break; }
			}
			if (win) return 1;
		}
	} //строка
	for (int j = 0; j < n; j++) {
		for (int i = 0; i <= m - l; i++) {
			int win = 1;
			for (int k = 0; k < l; k++) {
				if (board[i + k][j] != sym) { win = 0; break; }
			}
			if (win) return 1;
		}
	} //столбец
	for (int i = 0; i <= m - l; i++) {
		for (int j = 0; j <= n - l; j++) {
			int win = 1;
			for (int k = 0; k < l; k++) {
				if (board[i + k][j + k] != sym) { win = 0; break; }
			}
			if (win) return 1;
		}
	} //диагональ вправо-вниз
	for (int i = 0; i <= m - l; i++) {
		for (int j = l - 1; j < n; j++) {
			int win = 1;
			for (int k = 0; k < l; k++) {
				if (board[i + k][j - k] != sym) { win = 0; break; }
			}
			if (win) return 1;
		}
	} //диагональ влево-вниз
	return 0;
}




int main() {
	setlocale(LC_ALL, "");
	int m, n, l;
	printf("%s", "Введите размер полей (число строк, число столбцов): \n");
	scanf("%d %d", &m, &n);
	printf("%s", "Введите длину строки, при которой будет достигаться победа: \n");
	scanf("%d", &l);

	if (m <= 0 || n <= 0 || l < 1 || l > m || l > n) { return 0; }

	int maxm = category(m);
	int maxn = category(n);

	char sym1, sym2;
	printf("Игрок 1, введите ваш символ: \n");
	scanf(" %c", &sym1);
	printf("Игрок 2, введите ваш символ: \n");
	scanf(" %c", &sym2);



	while (sym1 == sym2) {
		printf("Игрок 2, введите другой символ: \n");
		scanf(" %c", &sym2);
	}

	char** board = (char**)malloc(m * sizeof(char*));
	for (int i = 0; i < m; i++) {
		board[i] = (char*)malloc(n * sizeof(char));
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = '.';
		}
	}



	int turn = 0;
	int game_over = 0;



	while (!game_over) {
		print_b(m, n, maxm, maxn, board);
		char sym = (turn == 0) ? sym1 : sym2;
		int r, c;
		printf("Игрок %d (%c), введите строку и столбец через пробел: \n", turn + 1, sym);
		scanf("%d %d", &r, &c);

		if (r < 1 || r > m || c < 1 || c > n) {
			printf("Неверные координаты! Попробуйте снова.\n");
			continue;
		}
		if (board[r - 1][c - 1] != '.') {
			printf("Клетка занята! Попробуйте снова.\n");
			continue;
		}
		board[r - 1][c - 1] = sym;
		if (check(m, n, l, board, sym)) {
			print_b(m, n, maxm, maxn, board);
			printf("Игрок %d (%c) победил!", turn + 1, sym);
			game_over = 1;
		}
		else {
			turn = 1 - turn;
		}
	}
	return 0;
}
