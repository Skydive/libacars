{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "libacars";
  src = ./.;

  enableParallelBuilding = true;

  outputs = [ "out" "dev" ];

  buildInputs = with pkgs; [ 
    pkgconfig
    cmake
  ];

  propagatedBuildInputs = with pkgs; [
    zlib
    libxml2
  ];

  configurePhase = ''
    mkdir -p build && cd build
    cmake ../
  '';

  buildPhase = ''
    make -j8
  '';

  installPhase = ''
    mkdir -p $out/lib
    cp libacars/libacars-2.so.2 $out/lib
    cp libacars/libacars-2.so $out/lib
    cp libacars/libacars-2.a $out/lib
    mkdir -p $out/lib/pkgconfig
  '';
}