
FROM golang:1.22 AS build-stage

WORKDIR /app

COPY go.mod ./
COPY . ./ 

RUN CGO_ENABLED=0 GOOS=linux go build -o /sb-server ./cmd/fe-proto/main.go

FROm alpine:3.19.1

WORKDIR /

COPY --from=build-stage /sb-server /sb-server

EXPOSE 8080

ENTRYPOINT ["/sb-server"]
