


## Score: 25/25 (100.00%)


### ✓ - [0/0] - Output from `make`

- **Points**: 0 / 0


```
sed -i 's/wallet_destory/wallet_destroy/g' lib/wallet.h
g++-9 -Ilib -W -Wall -g -c test.cpp -o test.o
sed -i 's/wallet_destory/wallet_destroy/g' lib/wallet.c
sed -i 's/wallet_destory/wallet_destroy/g' lib/wallet.h
g++-9 -x c -Ilib -W -Wall -g -c lib/wallet.c -o lib/wallet.o
g++-9 lib/wallet.o test.o -o test -pthread

```


### ✓ - [5/5] - test degree.c works

- **Points**: 5 / 5





### ✓ - [5/5] - test large adds

- **Points**: 5 / 5





### ✓ - [5/5] - test multiple wallets

- **Points**: 5 / 5





### ✓ - [5/5] - test initial negative delta

- **Points**: 5 / 5





### ✓ - [5/5] - test initial get resource

- **Points**: 5 / 5





---

This report was generated for **kjzhou2** using **ec3de291470422a9d098655c36a54082ad6bd8da** (from **March 16th 2021, 2:00:00 am**)
