
FROM custom_builder:1.0

WORKDIR /app

COPY . ./
COPY ./lib/libnghttp2_asio.so /usr/lib
RUN ldconfig

RUN make 

RUN export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/nghttp2-asio/build/lib/

EXPOSE 8085

CMD ["/app/build/Server"]
