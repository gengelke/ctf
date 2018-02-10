Bandit Level 15 → Level 16
==========================

Level Goal
----------

The password for the next level can be retrieved by submitting the password of the current level to port 30001 on localhost using SSL encryption.

Helpful note: Getting “HEARTBEATING” and “Read R BLOCK”? Use -ign_eof and read the “CONNECTED COMMANDS” section in the manpage. Next to ‘R’ and ‘Q’, the ‘B’ command also works in this version of that command…

Commands you may need to solve this level
-----------------------------------------

ssh, telnet, nc, openssl, s_client, nmap

Helpful Reading Material
------------------------

[Secure Socket Layer/Transport Layer Security on Wikipedia](http://en.wikipedia.org/wiki/Secure_Socket_Layer)

[OpenSSL Cookbook - Testing with OpenSSL](https://www.feistyduck.com/library/openssl-cookbook/online/ch-testing-with-openssl.html)


Solution
========

The text tells us that we have to connect to the SSL port 30001 on host localhost. So that's what we do first:

```
bandit15@bandit:~$ openssl s_client -connect localhost:30001
CONNECTED(00000003)
depth=0 CN = 8f75dc271013
verify error:num=18:self signed certificate
verify return:1
depth=0 CN = 8f75dc271013
verify return:1
---
Certificate chain
 0 s:/CN=8f75dc271013
   i:/CN=8f75dc271013
---
Server certificate
-----BEGIN CERTIFICATE-----
MIICvjCCAaagAwIBAgIJALADbwWQ0u9aMA0GCSqGSIb3DQEBCwUAMBcxFTATBgNV
BAMTDDhmNzVkYzI3MTAxMzAeFw0xNzA5MTYwNzAyMjRaFw0yNzA5MTQwNzAyMjRa
MBcxFTATBgNVBAMTDDhmNzVkYzI3MTAxMzCCASIwDQYJKoZIhvcNAQEBBQADggEP
ADCCAQoCggEBALmjBUTlmjROJUssm+rAlFADFfzrz+xCH0qUXryou5/wW8pnQ6nG
HbdeRIBwTVGFiDIKRbFdWQU4BbrfjEhyGn9d7eh/3GV09ZdvLDYRoLmJ4tDF8CiC
wGl9GufcWr3zeaNYa8CwVdtWam8umhMICrsv7B5iV9RdSQfudUtVbr26SBVyuhBm
m0t7Su6rLCrrGtshdIihjk4k67bBMpSNAOduhpp79UgIPKcwJUhRJHTcji3m/IQ8
O9zNS25oL8KhMn7e/Xe70kztstq0ShMsx8feutONnGulUOlaEMMqW+HSWgnVeG/r
mU9Nzwn++4qxe16OvvmXAzctH2RlDx7XbcsCAwEAAaMNMAswCQYDVR0TBAIwADAN
BgkqhkiG9w0BAQsFAAOCAQEADHODX5CcMLI5fdumzly5FAVg5Yc22eDGNhmyhi/N
kDhP6QYw+HW5nWEYapc9m/ZQGEEoxr+wj6qeEhscxRxpuEIcunZsLKcoAmToyXeO
ANMslQugRcGqN57Pt0h5VuctLMa3ickeVPFvV6gxJSHBNRK1iN8nrfsy+zR+stzI
xcjIuakDDxMKFtb/1TMKf4/EsimSQLS0WXLjbxfQ/J510O4/Of0tmZI0ZIG+cKmM
V5hAOtuuAk6jREfWYJQ3DB+phv7PO9s2FpofVJss5PK4NWDS7UQOv359ZOJ85ZpJ
ihGxDqV7IAHJZNM9lvFXz/+EOn1oTGW9V8bAwt34OVYoPw==
-----END CERTIFICATE-----
subject=/CN=8f75dc271013
issuer=/CN=8f75dc271013
---
No client certificate CA names sent
---
SSL handshake has read 1682 bytes and written 637 bytes
---
New, TLSv1/SSLv3, Cipher is DHE-RSA-AES256-SHA
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
SSL-Session:
    Protocol  : SSLv3
    Cipher    : DHE-RSA-AES256-SHA
    Session-ID: 7BA97F7127B85F957A3FFE7F8B259C72EBB640D14B27B2D83E833CFF46C43774
    Session-ID-ctx:
    Master-Key: EBF297B4BFF9B4BF184147F2845F28D50AAAA047ED9DF340423EE68B13131EAD6FCD9B2E71431DC3E5D22F0942937E14
    Key-Arg   : None
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    Start Time: 1509047295
    Timeout   : 300 (sec)
    Verify return code: 18 (self signed certificate)
---
```

Now the command waits for any input. So we paste the current level's password into stdin:

```
BfMYroe26WYalil77FoDi9qh59eK5xNr
HEARTBEATING
read R BLOCK
read:errno=0
```

Damn, unfortunately we get the HEARTBEATING and read R BLOCK messages mentioned in the text. Let's try the command's option ```-ign_eof``` and see what happens if we use the command line ```openssl s_client -ign_eof -connect localhost:30001``` and redirect the current level's password to stdin:

```
bandit15@bandit:~$ echo "BfMYroe26WYalil77FoDi9qh59eK5xNr" | openssl s_client -ign_eof -connect localhost:30001
[...]
---
Correct!
cluFn7wTiGryunymYOu4RcffSxQluehd
```

Bingo!
