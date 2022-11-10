# 程式介紹

此為使用 C 語言的 RM 模擬排程程式，主要是在 Console 環境下使用 I/O Redirection 來將測試檔餵入後執行檔內，然後產生 Exact test 與 sufficient test 與文字排程結果與圖形排程結果

# 檔案內容

main.c //主要執行檔
rm.h //放置各種 RM 排程用的函式
file1~file3 //測試檔 1 到 3 裡面的格式為 taskID:Period_time:computation_time 遇到 0 代表截止
makefile //makefile 編譯腳本

# 環境需求

需要有 C 的編譯環境

# 使用說明

1. 首先要先進入到 console 的環境裡，輸入 make 是直接編譯而已
2. 輸入 make test1 就會自動編譯並喂入 file1 的資料，接著輸出結果
   ```md
   假如輸入 make test1：
   RMS:U=0.7333<=0.8284
   exact test pass
   0:E:1
   1:E:2
   2:E:2
   3:E:1
   4:I
   5:E:2
   6:E:1
   7:E:2
   8:I
   9:E:1
   10:E:2
   11:E:2
   12:E:1
   13:I
   14:I
   T1 #--#--#--#--#--
   T2 -##--#-#--##---
   ```

```

```
