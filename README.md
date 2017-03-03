FFAssembler SIC/XE assemler
===

這個專案是臺中教育大學資工系的系統程式期末專題，
目的是要將SIC/XE組合語言組譯成為Object Code.

**開發者:**FloatFlower.Huang   
**聯絡我:**zxc110888asd@gmail.com

### 如何編譯:
方法1. 安裝[Qt C++ Framework Qt IDE](https://www.qt.io/)   
方法2. 手動編譯    
Ubuntu:
```shell
$ sudo apt-get install qt5base-dev qt5-qmake
$ qmake
$ make
```

使用方法查詢:
```shell
$ ./ff --help
$ ./ff -h
```

**編譯程式碼：**   
目前專案僅能編譯到TestData中的Figure2.5.txt   
編譯方法:    
```
$ ./ff --input PATH/TO/Figure2.1.txt --output PATH/TO/Figure2.1-Result.txt --mode 0
```
