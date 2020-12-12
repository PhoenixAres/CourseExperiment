.586
        DATA  SEGMENT USE16
         BUF  DB 'ABCDEBCDE23'
       COUNT  EQU $ - BUF
        DATA  ENDS
        CODE  SEGMENT USE16
              ASSUME CS: CODE, DS: DATA
        BEG:  MOV AX, DATA
              MOV DS, AX
              LEA BX, BUF
              MOV CX, COUNT
			  MOV DL, 0
      LAST1:  MOV AL, 42H
			  CMP [BX], AL
              JC NEXT1
              MOV AL, 46H
              CMP [BX], AL
              JNC NEXT1
              INC DL
      NEXT1:  INC BX
              LOOP LAST1
              MOV CX, 8
       LAST:  MOV AL, '0'         	
              ROL DL, 1             	
              JNC NEXT
              MOV AL, '1'         	
       NEXT:  MOV AH, 0EH
              INT 10H
              LOOP LAST
              MOV AH, 4CH
              INT 21H
        CODE  ENDS
              END BEG
