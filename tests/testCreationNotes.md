./qwirkle < <testname>.input > <testname>.gameout
diff -w <testname>.output <testname>.gameout
if [-e <testname>.expsave] diff -w -y <testname>.expsave <actual_gamesave>

please note: due to the use of the rand function, the tests may sometimes come out differently. Making sure TESTING is toggled to 'true' in LinkedList.cpp and running the test a few times usually provides the same output. 

to run all tests again:
./qwirkle < tests/TEST_BOARD_BOUNDS.input > tests/TEST_BOARD_BOUNDS.gameout;
./qwirkle < tests/TEST_CREDITS_AND_QUIT.input > tests/TEST_CREDITS_AND_QUIT.gameout;
./qwirkle < tests/TEST_ERROR_INVALID_MOVE.input > tests/TEST_ERROR_INVALID_MOVE.gameout;
./qwirkle < tests/TEST_LOAD_GAME_PLAY.input > tests/TEST_LOAD_GAME_PLAY.gameout;
./qwirkle < tests/TEST_LOAD_GAME_SAVE.input > tests/TEST_LOAD_GAME_SAVE.gameout;
./qwirkle < tests/TEST_PLACE_BOTH_PLAYERS.input > tests/TEST_PLACE_BOTH_PLAYERS.gameout;
./qwirkle < tests/TEST_PLACING_ONTO_EXISTING_TILE.input > tests/TEST_PLACING_ONTO_EXISTING_TILE.gameout;
./qwirkle < tests/TEST_QUIT_FROM_GAME.input > tests/TEST_QUIT_FROM_GAME.gameout;
./qwirkle < tests/TEST_QWIRKLE_EXCLAMATION_MARKS.input > tests/TEST_QWIRKLE_EXCLAMATION_MARKS.gameout;
./qwirkle < tests/TEST_REPLACE_BOTH_PLAYERS.input > tests/TEST_REPLACE_BOTH_PLAYERS.gameout;
./qwirkle < tests/TEST_SAVE_GAME_PLAY.input > tests/TEST_SAVE_GAME_PLAY.gameout;
./qwirkle < tests/TEST_TILE_NOT_IN_HAND.input > tests/TEST_TILE_NOT_IN_HAND.gameout;

