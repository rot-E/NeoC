set -eu

function clean() { # root-dir
	if [ -e NeoC ]; then
		rm -r NeoC
	fi

	if [ -e NeoC.a ]; then
		rm NeoC.a
	fi
}

function copy() { # root-dir
	mkdir NeoC
	cp -r src/* NeoC/
}

function retrieve() { # copied-src-dir
	local t

	if [ -n "$(ls)" ]; then
		for t in $(ls); do
			if [ -f $t ]; then
				mv $t ../
			fi

			if [ -d $t ]; then
				cd $t
				retrieve
				cd ../

				if [ -z "$(ls $t)" ]; then
					rmdir $t
				fi
			fi
		done
	fi
}

function compile() { # copied-src-dir
	# 環境 (Environment非依存)
	gcc -c Memory.c -o Memory.o -g

	# ライブラリ用初期化環境
	gcc -c Environment.c -o Environment.o -g

	# 環境 (Environment依存)
	gcc -c Exception.c -o Exception.o -g

	# 定義値
	cd SPEC
		gcc -c CC.c -o CC.o -g
		gcc -c CSI.c -o CSI.o -g
		gcc -c SGR.c -o SGR.o -g
	cd ../

	# 部品
	gcc -c String.c -o String.o -g
	gcc -c Console.c -o Console.o -g
	gcc -c System.c -o System.o -g
	gcc -c Socket.c -o Socket.o -g
}

function archive() { # copied-src-dir
	ar -cq ../NeoC.a *.o */*.o # 二重まで対応
}

function remove() { # copied-src-dir
	local t e

	if [ -n "$(ls)" ]; then
		for t in $(ls); do
			if [ -f $t ]; then
				e=$(echo $t | /usr/bin/sed 's/^.*\.\([^\.]*\)$/\1/')
				if [ $e = "c" ]; then
					rm $t
				fi
				if [ $e = "o" ]; then
					rm $t
				fi
			fi
			if [ -d $t ]; then
				cd $t
				remove
				cd ../
			fi
		done
	fi
}

function build() { # root-dir
	clean			# 掃除
	copy			# 複製

	cd NeoC
		retrieve	# 降下
	cd ../

	cd NeoC
		compile		# 翻訳
	cd ../

	cd NeoC
		archive		# 書庫作成
	cd ../

	cd NeoC
		remove		# *.h 残留
	cd ../
}

if [ $# == 0 ]; then
	build
	sh examples/build.sh
else
	clean
	sh examples/build.sh clean
fi
