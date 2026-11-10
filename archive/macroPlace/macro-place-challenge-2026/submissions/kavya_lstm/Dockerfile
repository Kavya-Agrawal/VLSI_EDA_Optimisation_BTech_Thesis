FROM pytorch/pytorch:2.5.1-cuda12.4-cudnn9-runtime

ENV DEBIAN_FRONTEND=noninteractive
WORKDIR /challenge

RUN apt-get update && apt-get install -y --no-install-recommends git \
    && rm -rf /var/lib/apt/lists/*

COPY macro_place/ /challenge/macro_place/
COPY pyproject.toml /challenge/pyproject.toml
COPY requirements.txt /challenge/requirements.txt
COPY external/MacroPlacement/Testcases/ICCAD04/ /challenge/external/MacroPlacement/Testcases/ICCAD04/
COPY external/MacroPlacement/CodeElements/Plc_client/ /challenge/external/MacroPlacement/CodeElements/Plc_client/

RUN pip install --no-cache-dir -e . && pip install --no-cache-dir scipy tqdm numpy

COPY submissions/kavya_lstm/ /challenge/submissions/kavya_lstm/

ENTRYPOINT ["python", "-m", "macro_place.evaluate"]
