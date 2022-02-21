gcc micro_paint.c -o micro_paint -Wall -Wextra -Werror
echo ""
echo "TEST - <ex_1>"
./micro_paint ./test/ex_1
echo ""
echo "TEST - <ex_2>"
./micro_paint ./test/ex_2
echo ""
echo "TEST - <ex_3>"
./micro_paint ./test/ex_3
echo ""
echo "TEST - <ex_4>"
./micro_paint ./test/ex_4
echo ""
echo "TEST - <NULL>"
./micro_paint
echo ""
echo "TEST - <Error file>"
./micro_paint ./test/ex
rm micro_paint