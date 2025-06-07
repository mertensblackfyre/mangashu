
let
  pkgs = import <nixpkgs> {};
in
  pkgs.mkShell {
    packages = [
    pkgs.gcc
    pkgs.imagemagickBig
];
  }
