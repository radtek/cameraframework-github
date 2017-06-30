重装了VS2010，在编译程序时出现了“error: LNK1123: failure during conversion to COFF: file invalid or corrupt ”这个错误，意思是由于COFF标识转换失败。而在连接中完成此项工作的是cvtres.exe。这个错误的原因是存在多个版本的cvtres.exe。

系统目录：C:\Windows\Microsoft.NET\Framework\v4.0.30319\cvtres.exe

    C:\Windows\Microsoft.Net\Framework64\v4.0.30319\cvtres.exe

VS目录：   C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\BIN\cvtres.exe

改名cvtres_old.exe