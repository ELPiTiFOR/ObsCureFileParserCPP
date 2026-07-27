$exePath = ".\build\ObsCureFileParser.exe"
$crlf = "`r`n"

function Test {
    param (
        [string]$testName,
        [string]$argumentList,
        [string]$expectedExitCode,
        [string]$expectedOutput,
        [string]$expectedErrorOutput
    )

    $tempFile = [System.IO.Path]::GetTempFileName()
    $errorFile = [System.IO.Path]::GetTempFileName()

    if ($argumentList -eq "")
    {
        $process = Start-Process -FilePath $exePath -RedirectStandardOutput $tempFile -RedirectStandardError $errorFile -Wait -PassThru
    }
    else {
        $process = Start-Process -FilePath $exePath -ArgumentList $argumentList -RedirectStandardOutput $tempFile -RedirectStandardError $errorFile -Wait -PassThru
    }

    $actualOutput = (Get-Content $tempFile -Raw)
    $actualErrorOutput = (Get-Content $errorFile -Raw)
    if ($null -eq $actualOutput)
    {
        $actualOutput = ""
    }
    if ($null -eq $actualErrorOutput)
    {
        $actualErrorOutput = ""
    }

    if ($null -eq $expectedOutput)
    {
        $expectedOutput = ""
    }
    if ($null -eq $expectedErrorOutput)
    {
        $expectedErrorOutput = ""
    }

    if ($expectedOutput -ne "")
    {
        $expectedOutput = $expectedOutput + $crlf
    }
    if ($expectedErrorOutput -ne "")
    {
        $expectedErrorOutput = $expectedErrorOutput + $crlf
    }

    Remove-Item $tempFile
    Remove-Item $errorFile

    $failed = $false

    if ($process.ExitCode -ne $expectedExitCode)
    {
        Write-Host "[FAILED]" -ForegroundColor Red -NoNewline
        " {0}" -f $testName
        "Expected code: {0}" -f $expectedExitCode
        "Actual code: {0}" -f $process.ExitCode
        $failed = $true
    }

    if ((($expectedOutput -eq "") -and ($actualOutput -ne "")) -or ($expectedOutput -ne "" -and $actualOutput -ne ($expectedOutput)))
    {
        Write-Host "[FAILED]" -ForegroundColor Red -NoNewline
        " {0}" -f $testName
        Write-Host "Expected output: '$expectedOutput'" -ForegroundColor Gray
        Write-Host "Actual output: '$actualOutput'" -ForegroundColor Gray
        $failed = $true
    }

    if ((($expectedErrorOutput -eq "") -and ($actualErrorOutput -ne "")) -or ($expectedErrorOutput -ne "" -and $actualErrorOutput -ne ($expectedErrorOutput)))
    {
        Write-Host "[FAILED]" -ForegroundColor Red -NoNewline
        " {0}" -f $testName
        Write-Host "Expected error output: '$expectedErrorOutput'" -ForegroundColor Gray
        Write-Host "Actual error output: '$actualErrorOutput'" -ForegroundColor Gray
        $failed = $true
    }

    if ($failed -eq $false)
    {
        Write-Host "[  OK  ]" -ForegroundColor Green -NoNewline
        " {0}" -f $testName
    }
}

Test "NoArgsShowHelp" "" 0 "usage: ObsCureFileParser --it-parse <path>" ""
Test "UnknownCommand" "--unknown-command" 3 "" "Unknown command `"--unknown-command`""
Test "ParseItFileMissingPath" "--it-parse" 2 "" "Please provide a path after `"--it-parse`""