---
layout: default
transition: slide-left
---

# 构建与跨平台

<style>
.deck-lead { margin-bottom: 0.5rem; font-size: 0.88rem; line-height: 1.4; }
.compact-html-table th, .compact-html-table td { padding: 0.45rem 0.6rem; font-size: 0.78rem; }
.compact-html-table.mb-6 { margin-bottom: 0.6rem !important; }
pre.shiki { font-size: 0.7rem !important; padding: 0.55rem 0.75rem !important; line-height: 1.45; }
.eyebrow { font-size: 0.7rem; margin-bottom: 0.3rem; }
.support-grid { gap: 0.4rem; }
.support-grid.mt-5 { margin-top: 0.5rem !important; }
.support-row { padding-bottom: 0.4rem; gap: 0.6rem; grid-template-columns: 6rem 1fr; }
.support-key { font-size: 0.74rem; }
.support-copy { font-size: 0.78rem; line-height: 1.4; }
.thin-divider { margin: 0.4rem 0 0.5rem; }
</style>

<div class="deck-rule"></div>

<div class="deck-lead">
  构建层的重点是把环境差异前置到 preset 里，不让 Qt 路径、生成器和测试命令散落在 README 或口头说明里。
</div>

<table class="compact-html-table mb-6">
  <thead>
    <tr>
      <th>平台</th>
      <th>Configure Preset</th>
      <th>Build Preset</th>
      <th>Test Preset</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Windows</td>
      <td><code>windows-ucrt64-debug / release</code></td>
      <td><code>build-ucrt64-*</code></td>
      <td><code>test-ucrt64-debug</code></td>
    </tr>
    <tr>
      <td>Linux</td>
      <td><code>linux-debug / release</code></td>
      <td><code>build-linux-*</code></td>
      <td><code>test-linux-debug</code></td>
    </tr>
    <tr>
      <td>macOS</td>
      <td><code>darwin-debug / release</code></td>
      <td><code>build-darwin-*</code></td>
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

<div class="support-grid mt-5">
  <div v-click class="support-row">
    <div class="support-key">Windows</div>
    <div class="support-copy">当前主验证路径是 MSYS2 UCRT64，把 Qt 路径、生成器、测试命令都固定在 preset 里。</div>
  </div>
  <div v-click class="support-row">
    <div class="support-key">macOS</div>
    <div class="support-copy">preset 自动找 Homebrew Qt 路径（<code>/opt/homebrew/opt/qt</code>），用 <code>CMAKE_PREFIX_PATH</code> 覆盖以支持 Qt 安装版。</div>
  </div>
</div>

<!--
各位老师，这一页我讲构建系统的设计。CMake Presets v6 是统一入口，三套平台各自有 configure / build / test preset。我把 Qt 路径、生成器、测试命令全部固定在 preset 里，不让它们散落在 README 或口头说明里——这样不同人、不同机器跑出来的命令是一致的。Windows 主验证路径是 MSYS2 UCRT64，因为 MSVC 环境的系统库配置更复杂。macOS preset 自动找 Homebrew Qt 路径，也支持通过 CMAKE_PREFIX_PATH 切换到 Qt 安装版。配置、构建、测试三步的命令是固定的，CI 上跑同一组命令就能复现。下面进入设计取舍那一页。
-->
