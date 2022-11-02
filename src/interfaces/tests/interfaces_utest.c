#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

/* xmalloc, FREE_SAFE */
#include "utils/memory.h"

/* load api */
#include "plugin/api/interfaces/load.h"

/* interfaces hash table state */
#include "plugin/data/interfaces/interface_state.h"

/* interfaces interface linked list */
#include "plugin/data/interfaces/interface/linked_list.h"

/* init functionality */
static int setup(void **state);
static int teardown(void **state);

/* tests */

/** interface hash table state **/
static void test_state_hash_new_correct(void **state);
static void test_state_hash_element_new_correct(void **state);
static void test_state_hash_add_correct(void **state);
static void test_state_hash_add_incorrect(void **state);
static void test_state_hash_get_correct(void **state);
static void test_state_hash_get_incorrect(void **state);
static void test_state_hash_set_name_correct(void **state);
static void test_state_hash_set_name_incorrect(void **state);

/* load */
static void test_correct_load_interface(void **state);

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_correct_load_interface),
		cmocka_unit_test(test_state_hash_new_correct),
		cmocka_unit_test(test_state_hash_element_new_correct),
		cmocka_unit_test(test_state_hash_add_correct),
		cmocka_unit_test(test_state_hash_add_incorrect),
		cmocka_unit_test(test_state_hash_get_correct),
		cmocka_unit_test(test_state_hash_get_incorrect),
		cmocka_unit_test(test_state_hash_set_name_correct),
		cmocka_unit_test(test_state_hash_set_name_incorrect),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

static int setup(void **state)
{
	interfaces_ctx_t *ctx = xmalloc(sizeof(interfaces_ctx_t));
	if (!ctx) {
		return -1;
	}

	*ctx = (interfaces_ctx_t){0};
	*state = ctx;

	return 0;
}

static int teardown(void **state)
{
	if (*state) {
		FREE_SAFE(*state);
	}

	return 0;
}

static void test_correct_load_interface(void **state)
{
    (void) state;

    int rc = 0;

    assert_int_equal(rc, 0);
}

static void test_state_hash_new_correct(void **state)
{
    (void) state;

    interfaces_interface_state_hash_element_t *state_hash; 

    state_hash = interfaces_interface_state_hash_new();
    assert_null(state_hash);
}

static void test_state_hash_element_new_correct(void **state)
{
    (void) state;

    interfaces_interface_state_hash_element_t *new_elem; 

    new_elem = interfaces_interface_state_hash_element_new();
    assert_non_null(new_elem);

    interfaces_interface_state_hash_element_free(&new_elem);
    assert_null(new_elem);
}

static void test_state_hash_add_correct(void **state)
{
    (void) state;

    int rc = 0;

    interfaces_interface_state_hash_element_t *state_hash, *new_elem; 

    state_hash = interfaces_interface_state_hash_new();
    assert_null(state_hash);

    new_elem = interfaces_interface_state_hash_element_new();

    interfaces_interface_state_hash_element_set_name(&new_elem, "FOO");
    assert_int_equal(rc, 0);

    rc = interfaces_interface_state_hash_add(&state_hash, new_elem);
    assert_int_equal(rc, 0);

    interfaces_interface_state_hash_free(&state_hash);
}

static void test_state_hash_add_incorrect(void **state)
{
    (void) state;

    int rc = 0;

    interfaces_interface_state_hash_element_t *state_hash, *new_elem; 

    state_hash = interfaces_interface_state_hash_new();
    assert_null(state_hash);

    new_elem = interfaces_interface_state_hash_element_new();

    interfaces_interface_state_hash_element_set_name(&new_elem, "FOO");
    assert_int_equal(rc, 0);

    rc = interfaces_interface_state_hash_add(&state_hash, new_elem);
    assert_int_equal(rc, 0);

    /* try adding the same element */
    rc = interfaces_interface_state_hash_add(&state_hash, new_elem);
    assert_int_not_equal(rc, 0);

    interfaces_interface_state_hash_free(&state_hash);
}

static void test_state_hash_get_correct(void **state)
{
    (void) state;

    int rc = 0;
    const char *name = "FOO";

    interfaces_interface_state_hash_element_t *state_hash, *new_elem, *found; 

    state_hash = interfaces_interface_state_hash_new();
    assert_null(state_hash);

    new_elem = interfaces_interface_state_hash_element_new();

    interfaces_interface_state_hash_element_set_name(&new_elem, name);
    assert_int_equal(rc, 0);

    rc = interfaces_interface_state_hash_add(&state_hash, new_elem);
    assert_int_equal(rc, 0);

    found = interfaces_interface_state_hash_get(state_hash, name);
    assert_non_null(found);

    interfaces_interface_state_hash_free(&state_hash);
}

static void test_state_hash_get_incorrect(void **state)
{
    (void) state;

    int rc = 0;
    const char *names[] = { "FOO", "BAR" };

    interfaces_interface_state_hash_element_t *state_hash, *new_elem, *found; 

    state_hash = interfaces_interface_state_hash_new();
    assert_null(state_hash);

    new_elem = interfaces_interface_state_hash_element_new();

    interfaces_interface_state_hash_element_set_name(&new_elem, names[0]);
    assert_int_equal(rc, 0);

    rc = interfaces_interface_state_hash_add(&state_hash, new_elem);
    assert_int_equal(rc, 0);

    found = interfaces_interface_state_hash_get(state_hash, names[1]);
    assert_null(found);

    interfaces_interface_state_hash_free(&state_hash);
}

static void test_state_hash_set_name_correct(void **state)
{
    (void) state;

    int rc = 0;

    interfaces_interface_state_hash_element_t *new_elem; 

    new_elem = interfaces_interface_state_hash_element_new();

    rc = interfaces_interface_state_hash_element_set_name(&new_elem, "FOO");
    assert_int_equal(rc, 0);
}

static void test_state_hash_set_name_incorrect(void **state)
{
    (void) state;

    int rc = 0;

    interfaces_interface_state_hash_element_t *new_elem; 

    new_elem = interfaces_interface_state_hash_element_new();

    rc = interfaces_interface_state_hash_element_set_name(&new_elem, NULL);
    assert_int_not_equal(rc, 0);
}
