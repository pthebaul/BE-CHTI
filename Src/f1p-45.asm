	AREA Signal, DATA, READONLY
	export TabSig2
; fonction cosinus, frequence relative 1, phase -45 degres, amplitude max
; valeurs attendues pour k = 1 :
;	Re	0x5A82562C	env +sqrt(0.5) * 2^31
;	Im	0x5A82562C	env +sqrt(0.5) * 2^31
;	M2	0x3FFFCDE5	env 2^30
; pour 1 < k < 63
;	M2    < 0x0000000F

TabSig2
	dcw	0x0da8	;  0   3496  0.85352
	dcw	0x0e2f	;  1   3631  0.88647
	dcw	0x0ea7	;  2   3751  0.91577
	dcw	0x0f0e	;  3   3854  0.94092
	dcw	0x0f64	;  4   3940  0.96191
	dcw	0x0fa8	;  5   4008  0.97852
	dcw	0x0fd9	;  6   4057  0.99048
	dcw	0x0ff6	;  7   4086  0.99756
	dcw	0x0fff	;  8   4095  0.99976
	dcw	0x0ff6	;  9   4086  0.99756
	dcw	0x0fd9	; 10   4057  0.99048
	dcw	0x0fa8	; 11   4008  0.97852
	dcw	0x0f64	; 12   3940  0.96191
	dcw	0x0f0e	; 13   3854  0.94092
	dcw	0x0ea7	; 14   3751  0.91577
	dcw	0x0e2f	; 15   3631  0.88647
	dcw	0x0da8	; 16   3496  0.85352
	dcw	0x0d13	; 17   3347  0.81714
	dcw	0x0c72	; 18   3186  0.77783
	dcw	0x0bc5	; 19   3013  0.73560
	dcw	0x0b10	; 20   2832  0.69141
	dcw	0x0a53	; 21   2643  0.64526
	dcw	0x0990	; 22   2448  0.59766
	dcw	0x08c9	; 23   2249  0.54907
	dcw	0x0800	; 24   2048  0.50000
	dcw	0x0737	; 25   1847  0.45093
	dcw	0x0670	; 26   1648  0.40234
	dcw	0x05ad	; 27   1453  0.35474
	dcw	0x04f0	; 28   1264  0.30859
	dcw	0x043b	; 29   1083  0.26440
	dcw	0x038e	; 30    910  0.22217
	dcw	0x02ed	; 31    749  0.18286
	dcw	0x0258	; 32    600  0.14648
	dcw	0x01d1	; 33    465  0.11353
	dcw	0x0159	; 34    345  0.08423
	dcw	0x00f2	; 35    242  0.05908
	dcw	0x009c	; 36    156  0.03809
	dcw	0x0058	; 37     88  0.02148
	dcw	0x0027	; 38     39  0.00952
	dcw	0x000a	; 39     10  0.00244
	dcw	0x0000	; 40      0  0.00000
	dcw	0x000a	; 41     10  0.00244
	dcw	0x0027	; 42     39  0.00952
	dcw	0x0058	; 43     88  0.02148
	dcw	0x009c	; 44    156  0.03809
	dcw	0x00f2	; 45    242  0.05908
	dcw	0x0159	; 46    345  0.08423
	dcw	0x01d1	; 47    465  0.11353
	dcw	0x0258	; 48    600  0.14648
	dcw	0x02ed	; 49    749  0.18286
	dcw	0x038e	; 50    910  0.22217
	dcw	0x043b	; 51   1083  0.26440
	dcw	0x04f0	; 52   1264  0.30859
	dcw	0x05ad	; 53   1453  0.35474
	dcw	0x0670	; 54   1648  0.40234
	dcw	0x0737	; 55   1847  0.45093
	dcw	0x0800	; 56   2048  0.50000
	dcw	0x08c9	; 57   2249  0.54907
	dcw	0x0990	; 58   2448  0.59766
	dcw	0x0a53	; 59   2643  0.64526
	dcw	0x0b10	; 60   2832  0.69141
	dcw	0x0bc5	; 61   3013  0.73560
	dcw	0x0c72	; 62   3186  0.77783
	dcw	0x0d13	; 63   3347  0.81714
	end
