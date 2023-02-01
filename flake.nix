{
  description = "A library for decoding ACARS message contents.";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    flake-utils.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };

    in {
      defaultPackage = pkgs.callPackage ./default.nix {};
      devShell = pkgs.mkShell {
        name = "libacars-shell";
        buildInputs = with pkgs; [
          pkg-config
          zlib
          cmake
          libxml2
          # (import ./default.nix { inherit pkgs; })
        ];
      };
    });
}