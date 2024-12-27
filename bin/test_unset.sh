#!/bin/bash

echo -e "\n\n${BLUE}=== TEST unset =================================${NC}"

test_unset_commands() {
	run_test "unset VAR && echo \$VAR"
	run_test "unset nizar"
	run_test "unset PATH && ls -l"
}

test_unset_commands
