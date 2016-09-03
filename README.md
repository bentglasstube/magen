# Magen

Magen Audio Generator

An algorithmic audio generator for making something not unlike music, based on
[these experiments][1].

[1]: http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html

## Installation

Magen uses [bazel][2] for building and requires SDL2.  Once you have both of
these things installed, you can build with `bazel build :mage` and run with
`bazel run :magen`.  If you want to copy the binary to your path, you will also
have to copy the content directory where the bitmap font is stored.

[2]:  https://bazel.io

## Usage

The progam works by selecting one of the various generators and adjusting the
parameters to it to change the output.

Each generator has six adjustable variables which can be controlled in real time
to change the sound.  Use the left and right arrows to move the cursor and the
up and down arrows to adjust the variables.  Use tab to change the generator.
