/* -*- mode: c -*-
 * $Id: objinst.c 36673 2007-05-03 16:55:46Z laurov $
 * http://www.bagley.org/~doug/shootout/
 */

#include <stdio.h>
#include <stdlib.h>


enum {false, true};

#define TOGGLE \
    char state; \
    char (*value)(struct Toggle *); \
    struct Toggle *(*activate)(struct Toggle *)

#define DESTROY  free

typedef struct Toggle {
    TOGGLE;
} Toggle;

char toggle_value(Toggle *this) {
    return(this->state);
}
Toggle *toggle_activate(Toggle *this) {
    this->state = !this->state;
    return(this);
}
Toggle *init_Toggle(Toggle *this, char start_state) {
    this->state = start_state;
    this->value = toggle_value;
    this->activate = toggle_activate;
    return(this);
}
Toggle *new_Toggle(char start_state) {
    Toggle *this = (Toggle *)malloc(sizeof(Toggle));
    return(init_Toggle(this, start_state));
}


typedef struct NthToggle {
    Toggle base;
    int count_max;
    int counter;
} NthToggle;

NthToggle *nth_toggle_activate(NthToggle *this) {
    if (++this->counter >= this->count_max) {
	this->base.state = !this->base.state;
	this->counter = 0;
    }
    return(this);
}
NthToggle *init_NthToggle(NthToggle *this, int max_count) {
    this->count_max = max_count;
    this->counter = 0;
    this->base.activate = (Toggle *(*)(Toggle *))nth_toggle_activate;
    return(this);
}
NthToggle *new_NthToggle(char start_state, int max_count) {
    NthToggle *this = (NthToggle *)malloc(sizeof(NthToggle));
    this = (NthToggle *)init_Toggle((Toggle *)this, start_state);
    return(init_NthToggle(this, max_count));
}

