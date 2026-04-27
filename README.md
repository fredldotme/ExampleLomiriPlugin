# Lomiri Plugin API example

This repository showcases a simple plugin built for the Lomiri Desktop (https://lomiri.com).

## Implementation in the shell

The Lomiri shell accomplishes this via an embedded WASM runtime environment, "WebAssembly Micro Runtime".
This runtime allows for embedding a plugin loader into a project and allows running WebAssembly code.
"WAMR" specifically has additional features, like supporting TCP & UDP sockets, which are also pretty
useful to potential plugin projects.

## License

To be decided
