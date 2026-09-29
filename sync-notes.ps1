<#
    sync-notes.ps1
    把 Obsidian 主库的「51单片机学习笔记」镜像到本仓库的 notes\ 目录。

    用法（在本仓库根目录执行）：
        .\sync-notes.ps1
        powershell -ExecutionPolicy Bypass -File .\sync-notes.ps1

    说明：
        - 采用「镜像」而非「复制」：notes\ 是主库的完整快照
        - 主库中删掉的文件，notes\ 里也会被删掉
        - 主库路径变了，只改下面的 $Source 即可
#>

$ErrorActionPreference = 'Stop'

# Obsidian 主库中的 51 单片机笔记目录（权威来源）
$Source = 'D:\obsidian\qisimiaoxiang\奇思妙想\04_实验与项目\51单片机学习笔记'

# 本仓库的镜像目标目录
$Dest = Join-Path $PSScriptRoot 'notes'

if (-not (Test-Path -LiteralPath $Source)) {
    throw "找不到 Obsidian 笔记目录：$Source"
}

Write-Host "源：$Source" -ForegroundColor Cyan
Write-Host "到：$Dest" -ForegroundColor Cyan

# /MIR                  镜像：多余的删除、缺失的补齐、变动的覆盖
# /NFL /NDL /NJH /NJS   精简输出，不逐条打印
# /R:1 /W:1             失败只重试 1 次，每次等 1 秒
robocopy $Source $Dest /MIR /NFL /NDL /NJH /NJS /R:1 /W:1 | Out-Null

$code = $LASTEXITCODE
if ($code -ge 8) {
    throw "robocopy 执行失败，退出码 $code"
}

Write-Host "笔记已从 Obsidian 主库镜像到 notes\。" -ForegroundColor Green
