#include <stdio.h> //printf
#include <stdlib.h> //exit

/* open */
//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>

#include <ncurses.h>

void save() {
	;
}


void print_usage(char *program_name) {
	printf("Egor's text editor\n");
	printf("Usage: %s <text_file>\n", program_name);
}

int main(int argc, char **argv) {
	char buf[BUFSIZ];

	if (argc < 2) {
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	char *text_file_name = argv[1];
	int fd = open(text_file_name, O_RDWR);

	if (-1 == fd) {
		fprintf(stderr, "Can't open file %s, exit.\n", text_file_name);
		exit(EXIT_FAILURE);
	}

	ssize_t readed_cnt = read(fd, buf, BUFSIZ -1);

	if (-1 == readed_cnt) {
		fprintf(stderr, "Can't read from file %s, exit.\n", text_file_name);
		exit(EXIT_FAILURE);
	}

	buf[readed_cnt] = 0;

	if (initscr() == NULL ) {
		fprintf(stderr, "Error initialising ncurses, exit\n");
		exit(EXIT_FAILURE);
	}

	box(stdscr, 0, 0);
	#define SAVE_KEY_MSG "F2: Save"
	#define SEP_KEY_MSG " "
	#define QUIT_KEY_MSG "F10: Exit"
	mvprintw(LINES - 1, COLS - 3 - sizeof(SAVE_KEY_MSG) + 1 - sizeof(QUIT_KEY_MSG) + 1 - sizeof(SEP_KEY_MSG) + 1,
			 " %s%s%s ", SAVE_KEY_MSG, SEP_KEY_MSG, QUIT_KEY_MSG);
	wrefresh(stdscr);

	noecho();
	keypad(stdscr, true);

	WINDOW *editor_window = subwin(stdscr, LINES - 2, COLS - 2, 1, 1);
	//scrollok(editor_window, 1);
	wprintw(editor_window, "%s", buf);
	wrefresh(editor_window);
	wmove(editor_window, 0, 0);
	wrefresh(editor_window);

	int key;
	int y, x;
	while((key = getch()) != KEY_F(10)) { // while not pressed ESC

		switch(key) {
		case KEY_UP:
			getyx(editor_window, y, x);
			wmove(editor_window, y-1, x);
			wrefresh(editor_window);
			break;

		case KEY_DOWN:
			getyx(editor_window, y, x);
			wmove(editor_window, y+1, x);
			wrefresh(editor_window);
			break;

		case KEY_LEFT:
			getyx(editor_window, y, x);
			wmove(editor_window, y, x-1);
			wrefresh(editor_window);
			break;

		case KEY_RIGHT:
			getyx(editor_window, y, x);
			wmove(editor_window, y, x+1);
			wrefresh(editor_window);
			break;

		case KEY_HOME:
			break;

		case KEY_END:
			break;

		case KEY_F(2):
			save();
			break;

		default:
			waddch(editor_window, key);
			wrefresh(editor_window);
			break;
		}

	}

	endwin();
	exit(EXIT_SUCCESS);
}
