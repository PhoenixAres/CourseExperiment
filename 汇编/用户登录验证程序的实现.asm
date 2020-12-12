 .586
        DATA  SEGMENT USE16
        STR1  DB 30, ?, 30 DUP(?)  
		STR2  DB 30, ?, 30 DUP(?)
        STR3  DB 'B18111627'
		CNT1  EQU $ - STR3
		STR4  DB '100200'
        CNT2  EQU $ - STR4            	
        FLAG  DB 'N'    
        STR5  DB 'username: $'
		STR6  DB 'password: $'
		STR7  DB 'WELCOME!$'
		STR8  DB 'ERROR!$'
        DATA  ENDS
        CODE  SEGMENT USE16
              ASSUME CS: CODE, DS: DATA, ES: DATA
        BEG:  MOV AX, DATA
        　　  MOV DS, AX            	
        　　  MOV ES, AX 
              MOV DX, OFFSET STR5
			  MOV AH, 09H
			  INT 21H
			  MOV DX, OFFSET STR1
			  MOV AH, 0AH
			  INT 21H
			  MOV DL, 0AH
			  MOV AH, 02H
			  INT 21H
			  MOV DX, OFFSET STR6
			  MOV AH, 09H
			  INT 21H
			  MOV BX, OFFSET STR2
	   READ:  MOV AH, 07H
			  INT 21H 
			  CMP AL, 0DH
			  JZ LAST
			  MOV [BX+2], AL
			  INC BX
			  JMP READ
	   LAST:  MOV DL, 0AH
			  MOV AH, 02H
			  INT 21H
	          MOV CX, OFFSET STR2
              SUB BX, CX
              MOV CL, BL
          　  MOV CH, 0    	                          
              CMP CX, CNT2        	
              JNZ EXIT 	
              MOV SI, OFFSET STR4 	
              MOV DI, OFFSET STR2+2   	
              CLD 　　              	
              REPE CMPSB            	
              JNZ EXIT    
			  MOV CL, STR1+1
          　  MOV CH, 0    	                          
              CMP CX, CNT1       	
              JNZ EXIT 	
              MOV SI, OFFSET STR3 	
              MOV DI, OFFSET STR1+2 
			  CLD 　　              	
              REPE CMPSB            	
              JNZ EXIT 
	          MOV FLAG, 'Y' 
       EXIT:  CMP FLAG, 'Y'
              JZ RIGHT
			  MOV DX, OFFSET STR8
			  MOV AH, 09H
			  INT 21H
			  MOV DL, 0AH
			  MOV AH, 02H
			  INT 21H
			  JMP BEG 			  
      RIGHT:  MOV DX, OFFSET STR7
			  MOV AH, 09H
			  INT 21H
			  MOV DL, 0AH
			  MOV AH, 02H
			  INT 21H			  
              MOV AH, 4CH
              INT 21H
        CODE  ENDS
              END BEG
