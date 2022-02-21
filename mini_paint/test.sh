gcc mini_paint.c -o mini_paint -Wall -Wextra -Werror -lm
echo ""
echo "TEST - <ex_1>"
./mini_paint ./test/ex_1
echo ""
echo "TEST - <ex_2>"
./mini_paint ./test/ex_2
echo ""
echo "TEST - <NULL>"
./mini_paint
echo ""
echo "TEST - <Error file>"
./mini_paint ./test/ex
rm mini_paint
