#pragma once

/*抽象出按钮的行为*/
typedef int (*button_press_fn_t)(void *self);
typedef int (*button_release_fn_t)(void *self);
typedef int (*button_get_state_fn_t)(void *self);
typedef int (*button_get_num_fn_t)(void *self);

struct button_i {
	button_press_fn_t   	press;
	button_release_fn_t 	release;
	button_get_state_fn_t 	get_state;
	button_get_num_fn_t   	get_num;
};


