---
layout: default
transition: slide-left
---

# 构建与跨平台

<div class="deck-rule"></div>

<div class="deck-lead">
  构建层的重点是把环境差异前置到 preset 里，不让 Qt 路径、生成器和测试命令散落在 README 或口头说明里。
</div>

<table class="compact-html-table mb-5">
  <thead>
    <tr>
      <th>平台</th>
      <th>Configure Preset</th>
      <th>Test Preset</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Windows</td>
      <td><code>windows-ucrt64-debug / release</code></td>
      <td><code>test-ucrt64-debug</code></td>
    </tr>
    <tr>
      <td>Linux</td>
      <td><code>linux-debug / release</code></td>
      <td><code>test-linux-debug</code></td>
    </tr>
    <tr>
      <td>macOS</td>
      <td><code>darwin-debug / release</code></td>
      <td><code>test-darwin-debug</code></td>
    </tr>
  </tbody>
</table>

<div class="eyebrow">统一命令入口</div>
<div class="thin-divider"></div>

```bash
cmake --preset windows-ucrt64-debug
cmake --build --preset build-ucrt64-debug
ctest --preset test-ucrt64-debug --output-on-failure
```

<div class="support-grid mt-4">
  <div v-click class="support-row">
    <div class="support-key">Windows</div>
    <div class="support-copy">主验证路径 MSYS2 UCRT64，Qt 路径、生成器、测试命令固定在 preset 里。</div>
  </div>
  <div v-click class="support-row">
    <div class="support-key">macOS</div>
    <div class="support-copy">preset 自动找 Homebrew Qt 路径，<code>CMAKE_PREFIX_PATH</code> 支持 Qt 安装版。</div>
  </div>
  <div v-click class="support-row">
    <div class="support-key">CI/CD</div>
    <div class="support-copy">GitHub Actions 两套 workflow：CI（格式+构建+测试）+ Release（打包+发布）。</div>
  </div>
</div>

<!--
各位老师，CMake Presets v6 是统一入口。三套平台各有 configure/build/test preset。不同人、不同机器跑出来的命令是一致的。CI 上两套 workflow：一套负责日常格式、构建、测试，另一套负责打安装包并发布到 GitHub Release。
-->
