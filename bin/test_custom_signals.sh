#!/bin/bash

echo -e "\n\n${BLUE}=== TEST SIGNAL =================================${NC}"

test_signal_commands() {
	run_test "kill -2 0" # SIGTERM ctrl+c
	run_test "(cat | kill -3 0)" # SIGQUIT (core dump) ctrl+\
	run_test "(cat && (kill -2 0))" # SIGTERM ctrl+c
	run_test "(kill -3 0)" # SIGQUIT (core dump) ctrl+\
	run_test "echo a && (kill -2 0) && echo b" # SIGINT ctrl+c

}

# Call the signal test suite
test_signal_commands
