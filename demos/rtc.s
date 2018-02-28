	.global start
.code16			#使用16位模式汇编(GAS 默认认为 .S 文件是 pure 32-bits i386 code)
.text			#代码段开始(为 link script 做定位)

start:  jmp   main
	unit:.byte 9,8,7,6,4,2,0
	rtc:.ascii "00","/","00","/","00","-","00","-","00",":","00",":","00"

main:
        mov    %cs, %ax
        mov    %ax, %ds
        mov    %ax, %es

	mov    $rtc, %bp	#初始化要打印的字符串的开始位置
INF:
	mov    $unit, %si	#初始化%si为unit标记所在位置
	mov    $rtc, %di	#初始化%di为rtc标记所在位置

	call   getRTC		#读取时间信息
        call   printTime        #调用显示字符串例程

	jmp    INF	        #无限循环


getRTC:				#CMOS RAM数据单元: (%si) 目标位置：(%di)
	call checkStatus	#检查RTC状态寄存器的更新标志位

	mov (%si), %al		#从CMOS RAM相应的内存单元中读出年月日，时分秒
	call getTime		#读取时间
	call BCD2ASCII		#转换为ASCII码
	call saveTime		#存放到内存中

	inc %di			#di往后移动两个单元，以便指向rtc中对应的结果单元
	inc %di
	inc %si			#si往后移动一个单元，获取下一个寄存器地址
	cmp $rtc, %si		#如果读完了所有的寄存器单元，那么结束，否则continue
	jb getRTC
	ret

printTime:
        mov    $20, %cx            # CX = 串长度
        mov    $0x1301, %ax        # AH = 13,  AL = 01h
        mov    $0x00c, %bx        # 页号为0(BH = 0) 黑底红字(BL = 0Ch,高亮)
        mov    $0x00, %dl
        int    $0x10            # 10h 号中断
        ret

checkStatus:
	mov $0xA, %al
	out %al, $0x70
	in $0x71, %al
	test $0x80, %al          #检查状态寄存器A的第7位（最高位）1000 0000 0000 0000
	jnz checkStatus
	ret

getTime:
	out %al, $0x70
	in $0x71, %al
	ret

BCD2ASCII:
	mov %al, %ah		#把BCD码转化为ASCII码，例如00010010=>0001 0010=>1 2=>"1" "2"
	mov $4, %cl
	shr %cl, %ah		#得到每中时间数据的十位
	and $0x0F, %al		#得到每种时间数据的各位
	add $0x30, %ah		
	add $0x30, %al
	ret

saveTime:	
	mov %ah, (%di)
	inc %di
	mov %al, (%di)
	ret
.org 510            # 填充到 510 字节，使生成的二进制代码恰好为512字节
.word 0xaa55        # 结束标志
