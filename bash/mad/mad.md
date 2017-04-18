# mad(1)
	`mad(1)` is a markdown driven manual page viewer,
	this makes manuals easier to _write_, _reuse_, and
	_read_.

## Usage

	Usage: mad <file>

	Options:

	-U, --update       install and update remote man page
	-u, --update-self  update self 
	-h, --help         output this help information

## Installation

	Install `mad(1)` and its associated mad page.

	$ make install

	Uninstall both `mad(1)` and the associated mad page.

	$ make uninstall

## Page lookup

	Use the __MAD_PATH__ environment variable to control
	where `mad(1)` will look for a manual page.
	The ".md" extension **may be omitted**.

	For example:

	MAD_PATH=".:$HOME/.mad/share"

	The following paths will always be searched:

	- .
	- ~/.mad/share

