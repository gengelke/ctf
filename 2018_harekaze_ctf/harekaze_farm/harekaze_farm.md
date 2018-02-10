
Description

nc problem.harekaze.com 20328

In Harekaze Farm, some animas is living. Let’s find them!

file: harekaze_farm

(Pwn, 100 points)

$ file harekaze_farm
harekaze_farm: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=2a005d22b50d8bde2c2fcf1b0e0350b6d7f3d039, not stripped

$ strings harekaze_farm
[...]
Welcome to Harekaze farm
Input a name of your favorite animal:
sheep
goat
Begin to parade!
cow: "moo" "moo"
sheep: "baa" "baa"
goat: "bleat" "bleat"
hen: "cluck" "cluck"
isoroku
isoroku: "flag is here" "flag is here"
/home/harekaze_farm/flag
ERROR: FILE OPEN ERROR
[...]

$ objdump -d harekaze_farm
[...]
0000000000400806 <main>:
  400806:	55                   	push   %rbp
  400807:	48 89 e5             	mov    %rsp,%rbp
  40080a:	48 81 ec 30 01 00 00 	sub    $0x130,%rsp
  400811:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  400818:	00 00
  40081a:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  40081e:	31 c0                	xor    %eax,%eax
  400820:	48 8b 05 69 18 20 00 	mov    0x201869(%rip),%rax        # 602090 <stdin@@GLIBC_2.2.5>
  400827:	be 00 00 00 00       	mov    $0x0,%esi
  40082c:	48 89 c7             	mov    %rax,%rdi
  40082f:	e8 5c fe ff ff       	callq  400690 <setbuf@plt>
  400834:	48 8b 05 45 18 20 00 	mov    0x201845(%rip),%rax        # 602080 <stdout@@GLIBC_2.2.5>
  40083b:	be 00 00 00 00       	mov    $0x0,%esi
  400840:	48 89 c7             	mov    %rax,%rdi
  400843:	e8 48 fe ff ff       	callq  400690 <setbuf@plt>
  400848:	bf 18 0c 40 00       	mov    $0x400c18,%edi
  40084d:	e8 1e fe ff ff       	callq  400670 <puts@plt>
  400852:	c7 85 dc fe ff ff 00 	movl   $0x0,-0x124(%rbp)
  400859:	00 00 00
  40085c:	c7 85 dc fe ff ff 00 	movl   $0x0,-0x124(%rbp)
  400863:	00 00 00
  400866:	e9 6b 01 00 00       	jmpq   4009d6 <main+0x1d0>
  40086b:	48 c7 85 f0 fe ff ff 	movq   $0x0,-0x110(%rbp)
  400872:	00 00 00 00
  400876:	48 c7 85 f8 fe ff ff 	movq   $0x0,-0x108(%rbp)
  40087d:	00 00 00 00
  400881:	bf 38 0c 40 00       	mov    $0x400c38,%edi
  400886:	b8 00 00 00 00       	mov    $0x0,%eax
  40088b:	e8 10 fe ff ff       	callq  4006a0 <printf@plt>
  400890:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  400897:	b9 10 00 00 00       	mov    $0x10,%ecx
  40089c:	ba 10 00 00 00       	mov    $0x10,%edx
  4008a1:	48 89 c6             	mov    %rax,%rsi
  4008a4:	bf 00 00 00 00       	mov    $0x0,%edi
  4008a9:	b8 00 00 00 00       	mov    $0x0,%eax
  4008ae:	e8 ad fd ff ff       	callq  400660 <__read_chk@plt>
  4008b3:	48 98                	cltq
  4008b5:	48 89 85 e0 fe ff ff 	mov    %rax,-0x120(%rbp)
  4008bc:	48 8b 85 e0 fe ff ff 	mov    -0x120(%rbp),%rax
  4008c3:	48 83 e8 01          	sub    $0x1,%rax
  4008c7:	c6 84 05 f0 fe ff ff 	movb   $0x0,-0x110(%rbp,%rax,1)
  4008ce:	00
  4008cf:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  4008d6:	be 5f 0c 40 00       	mov    $0x400c5f,%esi
  4008db:	48 89 c7             	mov    %rax,%rdi
  4008de:	e8 ed fd ff ff       	callq  4006d0 <strcmp@plt>
  4008e3:	85 c0                	test   %eax,%eax
  4008e5:	75 28                	jne    40090f <main+0x109>
  4008e7:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
  4008ed:	48 98                	cltq
  4008ef:	48 c1 e0 03          	shl    $0x3,%rax
  4008f3:	48 8d 88 a0 20 60 00 	lea    0x6020a0(%rax),%rcx
  4008fa:	48 8b 85 f0 fe ff ff 	mov    -0x110(%rbp),%rax
  400901:	48 8b 95 f8 fe ff ff 	mov    -0x108(%rbp),%rdx
  400908:	48 89 01             	mov    %rax,(%rcx)
  40090b:	48 89 51 08          	mov    %rdx,0x8(%rcx)
  40090f:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  400916:	be 63 0c 40 00       	mov    $0x400c63,%esi
  40091b:	48 89 c7             	mov    %rax,%rdi
  40091e:	e8 ad fd ff ff       	callq  4006d0 <strcmp@plt>
  400923:	85 c0                	test   %eax,%eax
  400925:	75 28                	jne    40094f <main+0x149>
  400927:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
  40092d:	48 98                	cltq
  40092f:	48 c1 e0 03          	shl    $0x3,%rax
  400933:	48 8d 88 a0 20 60 00 	lea    0x6020a0(%rax),%rcx
  40093a:	48 8b 85 f0 fe ff ff 	mov    -0x110(%rbp),%rax
  400941:	48 8b 95 f8 fe ff ff 	mov    -0x108(%rbp),%rdx
  400948:	48 89 01             	mov    %rax,(%rcx)
  40094b:	48 89 51 08          	mov    %rdx,0x8(%rcx)
  40094f:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  400956:	be 69 0c 40 00       	mov    $0x400c69,%esi
  40095b:	48 89 c7             	mov    %rax,%rdi
  40095e:	e8 6d fd ff ff       	callq  4006d0 <strcmp@plt>
  400963:	85 c0                	test   %eax,%eax
  400965:	75 28                	jne    40098f <main+0x189>
  400967:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
  40096d:	48 98                	cltq
  40096f:	48 c1 e0 03          	shl    $0x3,%rax
  400973:	48 8d 88 a0 20 60 00 	lea    0x6020a0(%rax),%rcx
  40097a:	48 8b 85 f0 fe ff ff 	mov    -0x110(%rbp),%rax
  400981:	48 8b 95 f8 fe ff ff 	mov    -0x108(%rbp),%rdx
  400988:	48 89 01             	mov    %rax,(%rcx)
  40098b:	48 89 51 08          	mov    %rdx,0x8(%rcx)
  40098f:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  400996:	be 6e 0c 40 00       	mov    $0x400c6e,%esi
  40099b:	48 89 c7             	mov    %rax,%rdi
  40099e:	e8 2d fd ff ff       	callq  4006d0 <strcmp@plt>
  4009a3:	85 c0                	test   %eax,%eax
  4009a5:	75 28                	jne    4009cf <main+0x1c9>
  4009a7:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
  4009ad:	48 98                	cltq
  4009af:	48 c1 e0 03          	shl    $0x3,%rax
  4009b3:	48 8d 88 a0 20 60 00 	lea    0x6020a0(%rax),%rcx
  4009ba:	48 8b 85 f0 fe ff ff 	mov    -0x110(%rbp),%rax
  4009c1:	48 8b 95 f8 fe ff ff 	mov    -0x108(%rbp),%rdx
  4009c8:	48 89 01             	mov    %rax,(%rcx)
  4009cb:	48 89 51 08          	mov    %rdx,0x8(%rcx)
  4009cf:	83 85 dc fe ff ff 01 	addl   $0x1,-0x124(%rbp)
  4009d6:	83 bd dc fe ff ff 02 	cmpl   $0x2,-0x124(%rbp)
  4009dd:	0f 8e 88 fe ff ff    	jle    40086b <main+0x65>
  4009e3:	bf 72 0c 40 00       	mov    $0x400c72,%edi
  4009e8:	e8 83 fc ff ff       	callq  400670 <puts@plt>
  4009ed:	c7 85 dc fe ff ff 00 	movl   $0x0,-0x124(%rbp)
  4009f4:	00 00 00
  4009f7:	e9 5d 01 00 00       	jmpq   400b59 <main+0x353>
  4009fc:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
  400a02:	48 98                	cltq
  400a04:	48 c1 e0 03          	shl    $0x3,%rax
  400a08:	48 05 a0 20 60 00    	add    $0x6020a0,%rax
  400a0e:	be 5f 0c 40 00       	mov    $0x400c5f,%esi
  400a13:	48 89 c7             	mov    %rax,%rdi
  400a16:	e8 b5 fc ff ff       	callq  4006d0 <strcmp@plt>
  400a1b:	85 c0                	test   %eax,%eax
  400a1d:	75 0a                	jne    400a29 <main+0x223>
  400a1f:	bf 83 0c 40 00       	mov    $0x400c83,%edi
  400a24:	e8 47 fc ff ff       	callq  400670 <puts@plt>
  400a29:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
  400a2f:	48 98                	cltq
  400a31:	48 c1 e0 03          	shl    $0x3,%rax
  400a35:	48 05 a0 20 60 00    	add    $0x6020a0,%rax
  400a3b:	be 63 0c 40 00       	mov    $0x400c63,%esi
  400a40:	48 89 c7             	mov    %rax,%rdi
  400a43:	e8 88 fc ff ff       	callq  4006d0 <strcmp@plt>
  400a48:	85 c0                	test   %eax,%eax
  400a4a:	75 0a                	jne    400a56 <main+0x250>
  400a4c:	bf 94 0c 40 00       	mov    $0x400c94,%edi
  400a51:	e8 1a fc ff ff       	callq  400670 <puts@plt>
  400a56:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
  400a5c:	48 98                	cltq
  400a5e:	48 c1 e0 03          	shl    $0x3,%rax
  400a62:	48 05 a0 20 60 00    	add    $0x6020a0,%rax
  400a68:	be 69 0c 40 00       	mov    $0x400c69,%esi
  400a6d:	48 89 c7             	mov    %rax,%rdi
  400a70:	e8 5b fc ff ff       	callq  4006d0 <strcmp@plt>
  400a75:	85 c0                	test   %eax,%eax
  400a77:	75 0a                	jne    400a83 <main+0x27d>
  400a79:	bf a7 0c 40 00       	mov    $0x400ca7,%edi
  400a7e:	e8 ed fb ff ff       	callq  400670 <puts@plt>
  400a83:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
  400a89:	48 98                	cltq
  400a8b:	48 c1 e0 03          	shl    $0x3,%rax
  400a8f:	48 05 a0 20 60 00    	add    $0x6020a0,%rax
  400a95:	be 6e 0c 40 00       	mov    $0x400c6e,%esi
  400a9a:	48 89 c7             	mov    %rax,%rdi
  400a9d:	e8 2e fc ff ff       	callq  4006d0 <strcmp@plt>
  400aa2:	85 c0                	test   %eax,%eax
  400aa4:	75 0a                	jne    400ab0 <main+0x2aa>
  400aa6:	bf bd 0c 40 00       	mov    $0x400cbd,%edi
  400aab:	e8 c0 fb ff ff       	callq  400670 <puts@plt>
  400ab0:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
  400ab6:	48 98                	cltq
  400ab8:	48 c1 e0 03          	shl    $0x3,%rax
  400abc:	48 05 a0 20 60 00    	add    $0x6020a0,%rax
  400ac2:	be d2 0c 40 00       	mov    $0x400cd2,%esi
  400ac7:	48 89 c7             	mov    %rax,%rdi
  400aca:	e8 01 fc ff ff       	callq  4006d0 <strcmp@plt>
  400acf:	85 c0                	test   %eax,%eax
  400ad1:	75 7f                	jne    400b52 <main+0x34c>
  400ad3:	bf e0 0c 40 00       	mov    $0x400ce0,%edi
  400ad8:	e8 93 fb ff ff       	callq  400670 <puts@plt>
  400add:	48 8d 95 f0 fe ff ff 	lea    -0x110(%rbp),%rdx
  400ae4:	b8 00 00 00 00       	mov    $0x0,%eax
  400ae9:	b9 20 00 00 00       	mov    $0x20,%ecx
  400aee:	48 89 d7             	mov    %rdx,%rdi
  400af1:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  400af4:	be 07 0d 40 00       	mov    $0x400d07,%esi
  400af9:	bf 09 0d 40 00       	mov    $0x400d09,%edi
  400afe:	e8 dd fb ff ff       	callq  4006e0 <fopen@plt>
  400b03:	48 89 85 e8 fe ff ff 	mov    %rax,-0x118(%rbp)
  400b0a:	48 83 bd e8 fe ff ff 	cmpq   $0x0,-0x118(%rbp)
  400b11:	00
  400b12:	75 14                	jne    400b28 <main+0x322>
  400b14:	bf 22 0d 40 00       	mov    $0x400d22,%edi
  400b19:	e8 52 fb ff ff       	callq  400670 <puts@plt>
  400b1e:	bf 01 00 00 00       	mov    $0x1,%edi
  400b23:	e8 c8 fb ff ff       	callq  4006f0 <exit@plt>
  400b28:	48 8b 95 e8 fe ff ff 	mov    -0x118(%rbp),%rdx
  400b2f:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  400b36:	be ff 00 00 00       	mov    $0xff,%esi
  400b3b:	48 89 c7             	mov    %rax,%rdi
  400b3e:	e8 7d fb ff ff       	callq  4006c0 <fgets@plt>
  400b43:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  400b4a:	48 89 c7             	mov    %rax,%rdi
  400b4d:	e8 1e fb ff ff       	callq  400670 <puts@plt>
  400b52:	83 85 dc fe ff ff 01 	addl   $0x1,-0x124(%rbp)
  400b59:	83 bd dc fe ff ff 02 	cmpl   $0x2,-0x124(%rbp)
  400b60:	0f 8e 96 fe ff ff    	jle    4009fc <main+0x1f6>
  400b66:	b8 00 00 00 00       	mov    $0x0,%eax
  400b6b:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  400b6f:	64 48 33 14 25 28 00 	xor    %fs:0x28,%rdx
  400b76:	00 00
  400b78:	74 05                	je     400b7f <main+0x379>
  400b7a:	e8 01 fb ff ff       	callq  400680 <__stack_chk_fail@plt>
  400b7f:	c9                   	leaveq
  400b80:	c3                   	retq
  400b81:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400b88:	00 00 00
  400b8b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
[...]
