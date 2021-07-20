#include <stdlib.h>
#include <stdio.h>

#include "doubly_linked_list.h"

struct browser {
	struct doubly_linked_node *current;
	struct doubly_linked_list *history;
};

struct browser *browser_init(char *home)
{
	struct browser *b = (struct browser *)calloc(1, sizeof(struct browser));
	b->history = doubly_linked_list_init();
	doubly_linked_list_append(b->history, home);
	b->current = doubly_linked_list_get_tail(b->history);
	return b;
}

void browser_destroy(struct browser **browser)
{
	doubly_linked_list_free_nodes((*browser)->history);
	doubly_linked_list_free(&(*browser)->history);
	free(*browser);
	*browser = NULL;
}

void browser_go_back(struct browser *browser)
{
	if (doubly_linked_list_get_size(browser->history) == 1) return;
	doubly_linked_node_move_prev(&browser->current);
}

void browser_go_forward(struct browser *browser)
{
	if (doubly_linked_list_get_tail(browser->history) == browser->current) return;
	doubly_linked_node_move_next(&browser->current);
}

void browser_go_to(struct browser *browser, char *url)
{
	while(doubly_linked_list_get_tail(browser->history) != browser->current) {
		doubly_linked_list_delete_last(browser->history);
	}
	doubly_linked_list_append(browser->history, url);
	browser_go_forward(browser);
}

char *browser_get_current(struct browser *browser)
{
	return doubly_linked_node_get_data(browser->current);
}

int main(void)
{
	struct browser *browser = browser_init("http://google.com");
	browser_go_to(browser, "http://something.com");
	printf("current url %s\n", browser_get_current(browser));
	browser_go_to(browser, "http://something_else.com");
	printf("current url %s\n", browser_get_current(browser));
	browser_go_to(browser, "http://something2.com");
	printf("current url %s\n", browser_get_current(browser));
	browser_go_to(browser, "http://something3.com");
	printf("current url %s\n", browser_get_current(browser));
	browser_go_back(browser);
	printf("current url %s\n", browser_get_current(browser));
	browser_go_back(browser);
	printf("current url %s\n", browser_get_current(browser));
	browser_go_back(browser);
	printf("current url %s\n", browser_get_current(browser));
	browser_go_forward(browser);
	printf("current url %s\n", browser_get_current(browser));
	browser_go_to(browser, "http://final-url.com");
	printf("current url %s\n", browser_get_current(browser));
	browser_go_forward(browser);
	printf("current url %s\n", browser_get_current(browser));
	browser_destroy(&browser);
	return 0;
}
