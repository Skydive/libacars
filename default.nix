{ pkgs ? import <nixpkgs> {} }:

let
  version = "2";
in
  pkgs.stdenv.mkDerivation {
    name = "libacars-${version}";
    src = ./.;

    outputs = [ "out" ];
    enableParallelBuilding = true;

    # setupHooks = [
      # ./move-lib64.sh
    # ];

    buildInputs = with pkgs; [ 
      pkgconfig
      cmake
      zlib
      libxml2
    ];

    # preInstallPhases = preInstallPhases ++ ''
      
      # rm libacars/libacars-2.pc
      # rm $out/lib/pkgconfig/
    # '';
  }