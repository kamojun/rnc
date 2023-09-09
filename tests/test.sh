function usage {
cat >&2 <<EOS
コマンドの説明
[options]
 -h | --help:      ヘルプを表示
 --no-build:       コンパイラをビルドしない
 --apple-silicon:  apple-silicon mac
 -d | --docker-image <VALUE>:  実行するdockerのイメージ名
EOS
exit 1
}

IMAGE=compilerbook
while [ "$#" != 0 ]; do
  case $1 in
    -h | --help      ) usage;;
    --no-build       ) NO_BUILD=true;;
    --apple-silicon  ) APPLE_SILICON=true;;
    -d | --docker-image ) shift; IMAGE=$1;;
    -* | --*         ) echo "$1 : invalid option" ;;
  esac
  shift
done

if ! ${NO_BUILD:-false}; then
  cargo build
fi

./target/debug/rnc tests/tests.c > bind/tmp.s
CMD="gcc -static -o tmp tmp.s && ./tmp"

if ${APPLE_SILICON:-false}; then
  docker run --rm --platform linux/amd64 --mount type=bind,src=$PWD/bind,dst=/home/user --workdir /home/user ${IMAGE} /bin/bash -c "$CMD"
else
  docker run --rm --mount type=bind,src=$PWD/bind,dst=/home/user --workdir /home/user ${IMAGE} /bin/bash -c "$CMD"
fi