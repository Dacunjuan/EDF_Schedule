# 程式介紹

此為使用 C 語言的 EDF 模擬排程程式，主要是在 Console 環境下使用 I/O Redirection 來將測試檔餵入後執行檔內，然後產生 Exact test 與 sufficient test 與文字排程結果與圖形排程結果

# 檔案內容

main.c //主要執行檔

EDF.h //放置各種 EDF 排程用的函式

file1~file3 //測試檔 1 到 3 裡面的格式為 taskID:Period_time:computation_time 遇到 0 代表截止

makefile //makefile 編譯腳本

# 環境需求

需要有 C 的編譯環境

# 使用說明

1. 首先要先進入到 console 的環境裡，輸入 make 是直接編譯而已
2. 輸入 make test3 就會自動編譯並喂入 file3 的資料，接著輸出結果
   ```md
   假如輸入 make test3：
   cc main.c && ./a.out < file3
   EDF:U=1.000000 <= 1
   Schedulability test pass
   0:E:1
   1:E:2
   2:E:1
   3:E:2
   T1 #-#-
   T2 -#-#
   ```

```

```
