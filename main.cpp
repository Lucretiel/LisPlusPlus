#include "liscpp.h"

using namespace std;

int main()
{
	ReadEvalPrint(
		
		(Let,
			tok(fold), (Lambda, tok(F), tok(I), tok(L),
				(If, (IsNil, tok(L)),
					tok(I),
					(tok(fold), tok(F), (tok(F), tok(I), (Car, tok(L))), (Cdr, tok(L))))),

			tok(insertSorted), (Lambda, tok(list), tok(elem),
				(If, (IsNil, tok(list)),
					(List, tok(elem)),
					(If, (Less, tok(elem), (Car, tok(list))),
						(Cons, tok(elem), tok(list)),
						(Cons, (Car, tok(list)), (tok(insertSorted), (Cdr, tok(list)), tok(elem)))))),

			tok(insertSort), (Lambda, tok(list), (tok(fold), tok(insertSorted), nil, tok(list))),

			tok(makeRandomList), (Lambda, tok(size), tok(min), tok(max),
				(If, (Equal, tok(size), 0),
					nil,
					(Cons, (Rand, tok(min), tok(max)), (tok(makeRandomList), (Sub, tok(size), 1), tok(min), tok(max))))),

			tok(list), (tok(makeRandomList), 300, 0, 10),

			tok(merge), (Lambda, tok(left), tok(right), 
				(Cond,
					(IsNil, tok(left)), tok(right),
					(IsNil, tok(right)), tok(left),
					(Less, (Car, tok(left)), (Car, tok(right))), (Cons, (Car, tok(left)), (tok(merge), (Cdr, tok(left)), tok(right))),
					(Cons, (Car, tok(right)), (tok(merge), tok(left), (Cdr, tok(right)))))),

			tok(split), (Lambda, tok(list), tok(length),
				(If, (Equal, tok(length), 0),
					(Cons, nil, tok(list)),
					(Let, tok(result), (tok(split), (Cdr, tok(list)), (Sub, tok(length), 1)),
						(Cons, (Cons, (Car, tok(list)), (Car, tok(result))), (Cdr, tok(result)))))),

			tok(length), (Lambda, tok(list), (tok(fold), (Lambda, tok(x), tok(y), (Add, tok(x), 1)), 0, tok(list))),

			tok(mergeSort), (Lambda, tok(list),
				(Cond, 
					(IsNil, tok(list)), nil,
					(IsNil, (Cdr, tok(list))), tok(list),
					(Let,
						tok(splitResult), (tok(split), tok(list), (Div, (tok(length), tok(list)), 2)),
						tok(left), (Car, tok(splitResult)),
						tok(right), (Cdr, tok(splitResult)),
						(tok(merge), (tok(mergeSort), tok(left)), (tok(mergeSort), tok(right)))))),

			(Print,
				"List: ", tok(list),
				/*"\nSorted:", (tok(insertSort), tok(list)),*/
				"\nLength:", (tok(length), tok(list)),
				"\nMerge Sorted:", (tok(mergeSort), tok(list))))
	);

	return 0;
}