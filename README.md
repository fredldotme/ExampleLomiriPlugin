# Lomiri Plugin API example

This repository showcases a simple plugin built for the Lomiri Desktop (https://lomiri.com).

## Implementation in the shell

The Lomiri shell accomplishes this via an embedded WASM runtime environment, "WebAssembly Micro Runtime".
This runtime allows for embedding a plugin loader into a project and allows running WebAssembly code.
"WAMR" specifically has additional features, like supporting TCP & UDP sockets and threads, which are also
pretty useful to potential plugin projects.

## How to build

- Get Tide IDE (https://snapcraft.io/tide-ide)
- Clone this repository
- Open the `example.pro` file using Tide
- Build or Release a build using the Play button

## License

To be decided
