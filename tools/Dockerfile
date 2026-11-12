# tools/Dockerfile — reproducible Linux environment for pv_resizer_evolve (amd64 or arm64).
#   docker build -t pv-rsz-evolve -f tools/Dockerfile .
#   docker run --rm -it -v "$PWD":/work -w /work pv-rsz-evolve make env-check
# The repo is mounted at run time; Bazel's cache persists in the named volume below.
FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
COPY tools/install_deps_linux.sh /tmp/install_deps_linux.sh
RUN bash /tmp/install_deps_linux.sh && rm -rf /var/lib/apt/lists/*
ENV PATH="/root/.local/bin:${PATH}"
VOLUME ["/root/.cache/bazel"]
WORKDIR /work
CMD ["bash"]
