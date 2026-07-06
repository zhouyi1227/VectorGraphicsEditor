---
layout: default
transition: slide-left
---

# 构建与跨平台

<div class="deck-rule"></div>

<div class="deck-lead">
  构建层的重点是让环境差异尽量前置到 preset 中，而不是把 Qt 路径、生成器和测试命令散落在 README 或口头说明里。
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
    <div class="support-copy">当前主验证路径是 MSYS2 UCRT64，而不是缺少系统库配置的 MSVC 环境。</div>
  </div>
</div>

<!--
这一页主要是工程化补充：我没有把构建说明散落在 README 和口头说明里，而是做成了标准化 preset。答辩时老师如果追问跨平台，这页能快速给出证据。
-->
