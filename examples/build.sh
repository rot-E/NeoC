set -eu

function clean() { # examples-dir
	if [ -e NeoC ]; then
		rm -r NeoC
	fi

	local t

	if [ -n "$(ls)" ]; then
		for t in $(ls); do
			if [ -f $t ]; then
				if [ "$(echo $t | /usr/bin/sed 's/^.*\.\([^\.]*\)$/\1/')" != "sh" ]; then
					if [ "$(echo $t | /usr/bin/sed 's/^.*\.\([^\.]*\)$/\1/')" != "c" ]; then
						rm $t
					fi
				fi
			fi
		done
	fi
}

function copy() { # root-dir
	cp -pr NeoC* examples/
}

function compile() { # examples-dir
	local t

	if [ -n "$(ls)" ]; then
		for t in $(ls); do
			if [ -f $t ]; then
				if [ "$(echo $t | /usr/bin/sed 's/^.*\.\([^\.]*\)$/\1/')" = "c" ]; then
					gcc $t NeoC.a -o "$(basename $t .c)" -g
				fi
			fi
		done
	fi
}

if [ $# == 0 ]; then
	cd examples
		clean
	cd ../

	copy
	cd examples
		compile
	cd ../
else
	cd examples
		clean
	cd ../
fi
