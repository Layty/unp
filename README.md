# 开坑unp[unix 网络环境编程]学习

## Github

- [我的学习记录以及代码](https://github.com/Layty/unp)
- [原书代码](https://github.com/unpbook/unpv13e)

## unp[unix 网络环境编程]学习 vscode环境搭建

1. vscode 下载安装 `Native Debug`,f5打开调试配置,或者按照我的文件直接覆盖就行
2. 参考`.vscode`的两个文件,其中`launch`不用修改
3. 如果想自己每次重新编译书本的源码,不使用默认的`Makefie`,则需修改`task.json`,这里主要就是增加头文件的路径和链接库的路径,这个参数定义在`unpv13e/Make.defines`
4. 这个参数其实可以随便找个`Makefile` 打印变量即可,我这里修改打印看了下

   ```Makefile
   dbg:
	echo${CC} ${CFLAGS} -o $@ daytimetcpcli.o ${LIBS}
    # echo gcc -I../lib -g -O2 -D_REENTRANT -Wall -o dbg daytimetcpcli.o ../libunp.a -lpthread
   ```

   ```json
    {
        "tasks": [
            {
                "type": "shell",
                "label": "gcc build active file",
                "command": "/usr/bin/gcc",
                // echo gcc -I../lib -g -O2 -D_REENTRANT -Wall -o dbg daytimetcpcli.o ../libunp.a -lpthread
                "args": [
                    "-ggdb3",
                    "-I",
                    "${fileDirname}/../lib",
                    "-D_REENTRANT",
                    "-Wall",
                    "${file}",
                    "-o",
                    "${fileDirname}/${fileBasenameNoExtension}",
                    "${fileDirname}/../libunp.a",
                    "-lpthread",
                ],
                "options": {
                    "cwd": "/usr/bin"
                }
            }
        ],
        "version": "2.0.0"
    }

    {
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "gcc - 生成和调试活动文件",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "gcc build active file",
            "miDebuggerPath": "/usr/bin/gdb"
        }
    ]
    }
   ```
