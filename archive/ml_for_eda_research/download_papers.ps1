# Downloads key ML-for-EDA papers (arXiv PDFs) into papers/<domain>/
# Run: powershell -ExecutionPolicy Bypass -File download_papers.ps1

$ErrorActionPreference = "Continue"
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$papers = Join-Path $root "papers"

# domain | arxiv id | filename
$list = @(
    @("placement", "2211.13382", "MaskPlace_NeurIPS2022.pdf"),
    @("placement", "2306.14744", "ChiPFormer_ICML2023.pdf"),
    @("placement", "2412.07822", "MacroRegulator_NeurIPS2024.pdf"),
    @("placement", "2407.12282", "ChipDiffusion_ICML2025.pdf"),
    @("placement", "2302.01415", "AutoDMP_ISPD2023.pdf"),
    @("routing",   "1906.08809", "DeepRL_GlobalRouting_2019.pdf"),
    @("logic_synthesis", "1911.04021", "DRiLLS_ASPDAC2020.pdf"),
    @("logic_synthesis", "2110.11292", "OpenABC-D_2021.pdf"),
    @("timing_power_routability", "2507.13355", "PGR-DRC_UnsupervisedDRC_2025.pdf"),
    @("llm_for_eda", "2312.08617", "RTLCoder_TCAD2025.pdf"),
    @("llm_for_eda", "2311.00176", "ChipNeMo_2023.pdf"),
    @("surveys", "2102.03357", "ML_for_EDA_Survey_TODAES2021.pdf"),
    @("surveys", "2202.13564", "ML_Placement_Routing_Overview_2022.pdf")
)

foreach ($item in $list) {
    $domain = $item[0]; $id = $item[1]; $name = $item[2]
    $outdir = Join-Path $papers $domain
    $out = Join-Path $outdir $name
    $url = "https://arxiv.org/pdf/$id"
    if (Test-Path $out) { Write-Host "SKIP (exists): $name"; continue }
    try {
        Invoke-WebRequest -Uri $url -OutFile $out -UserAgent "Mozilla/5.0" -TimeoutSec 60
        $sz = [math]::Round((Get-Item $out).Length/1KB,1)
        Write-Host "OK  $name  ($sz KB)"
    } catch {
        Write-Host "FAIL $name  <- $url  : $($_.Exception.Message)"
    }
}
Write-Host "Done."
