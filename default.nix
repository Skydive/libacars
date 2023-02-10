{ pkgs ? import <nixpkgs> {} }:

let
  version = "2";
in
  pkgs.stdenv.mkDerivation {
    name = "libacars-${version}";
    src = ./.;

    outputs = [ "out" "lib" "dev" ];
    enableParallelBuilding = true;

    # setupHooks = [
      # ./move-lib64.sh
    # ];

    nativeBuildInputs = with pkgs; [ 
      pkg-config
      cmake
    ];

    propagatedBuildInputs = with pkgs; [
      zlib
      libxml2
    ];

    # preInstallPhases = preInstallPhases ++ ''
      
      # rm libacars/libacars-2.pc
      # rm $out/lib/pkgconfig/
    # '';
  }