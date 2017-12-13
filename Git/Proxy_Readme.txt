1、设置代理：
张蕊的代理
git config --global http.proxy 'socks5://172.21.3.227:1080'
git config --global https.proxy 'socks5://172.21.3.227:1080'

明哥的代理
git config --global http.proxy 'socks5://172.21.3.227:1080'
git config --global https.proxy 'socks5://172.21.3.227:3128'

或：
速度较快：
git config --global http.proxy 'socks5://172.21.3.227:1080'
git config --global https.proxy 'socks5://172.21.3.227:2132'

速度一般：
git config --global http.proxy 'socks5://172.21.3.227:1080'
git config --global https.proxy 'socks5://172.21.3.227:2312'
2、取消代理：
git config --global --unset http.proxy
git config --global --unset https.proxy


http代理 

git config --global http.proxy http://127.0.0.1:1080
git config --global https.proxy https://127.0.0.1:1080

git config --global --unset http.proxy
git config --global --unset https.proxy


