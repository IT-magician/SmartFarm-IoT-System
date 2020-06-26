
Nginx: 1.17.9 (2020-03월)
Nginx-Rtmp-Module: 1.2.1 (2017-11월)
openssl-1.1.1d (2019-09월)
pcre-8.43 (2019-02월)
zlib-1.2.11 (2017-1월)


메이크파일 모듈 내용

--with-cc=cl --builddir=objs --prefix= --conf-path=conf/nginx.conf --pid-path=logs/nginx.pid 
--http-log-path=logs/access.log --error-log-path=logs/error.log --sbin-path=nginx.exe 
--http-client-body-temp-path=temp/client_body_temp --http-proxy-temp-path=temp/proxy_temp 
--http-fastcgi-temp-path=temp/fastcgi_temp --http-scgi-temp-path=temp/scgi_temp 
--http-uwsgi-temp-path=temp/uwsgi_temp --with-cc-opt=-DFD_SETSIZE=1024 
--with-pcre=objs/lib/pcre-8.43 --with-zlib=objs/lib/zlib-1.2.11 --with-select_module 
--with-http_v2_module --with-http_realip_module --with-http_addition_module 
--with-http_sub_module --with-http_dav_module --with-http_stub_status_module 
--with-http_flv_module --with-http_mp4_module --with-http_gunzip_module 
--with-http_gzip_static_module --with-http_auth_request_module --with-http_random_index_module 
--with-http_secure_link_module --with-http_slice_module --with-mail --with-stream 
--with-openssl=objs/lib/openssl-1.1.1c --with-openssl-opt=no-asm --with-http_ssl_module 
--with-mail_ssl_module --with-stream_ssl_module --add-module=objs/lib/nginx-rtmp-module-1.2.1


설정은 conf 폴더에 nginx.conf 수정

네이버 카페 http://cafe.naver.com/btest/459