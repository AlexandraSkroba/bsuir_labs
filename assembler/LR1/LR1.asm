;Изменить порядок следования байтов в регистре X, не используя команду XGDX

 org $8000
 ldx #$1f00
 pshx
 pula
 pulb
 psha
 pshb
 pulx