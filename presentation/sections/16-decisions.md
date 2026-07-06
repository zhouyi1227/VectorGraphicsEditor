---
layout: default
transition: slide-left
---

# 测试与质量保障

<div class="deck-rule"></div>

<div class="metric-strip mb-6">
  <div v-click class="metric">
    <div class="metric-value">5</div>
    <div class="metric-label">测试模块</div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">40</div>
    <div class="metric-label">测试函数</div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">2</div>
    <div class="metric-label">静态检查</div>
    <div class="metric-note">format / lint</div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">3</div>
    <div class="metric-label">跨平台预设</div>
    <div class="metric-note">Windows / Linux / macOS</div>
  </div>
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="eyebrow">测试覆盖点</div>
    <div class="thin-divider"></div>
    <div class="rail-list">
      <div v-click class="rail-item">
        <div class="rail-title"><code>ShapeDataTests</code> + <code>FileManagerTests</code></div>
        <div class="rail-copy">覆盖序列化往返、版本校验、非法图形、重复 ID 和 transform 合法性。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>CanvasGeometryTests</code></div>
        <div class="rail-copy">覆盖正交化、等比缩放、防翻转和 frame-to-frame 角点映射。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>ShapeItemTests</code> + <code>MainWindowTests</code></div>
        <div class="rail-copy">覆盖路径构建、命中区域、preview 行为，以及 <code>Tools</code> 菜单 1 / 3 / 4 分组回归。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">GATE 01</div>
      <div class="rail-title"><code>clang-format --dry-run --Werror</code></div>
      <div class="rail-copy">保证风格一致，不让重构引入低价值格式漂移。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">GATE 02</div>
      <div class="rail-title"><code>clang-tidy</code></div>
      <div class="rail-copy">检查 bugprone、analyzer、modernize 和 performance 类问题。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">GATE 03</div>
      <div class="rail-title"><code>ctest --output-on-failure</code></div>
      <div class="rail-copy">用自动化回归替代“手点很多次”的主观判断。</div>
    </div>
  </div>
</div>

<!--
这页强调“可验证性”。课程项目最容易被问到“你怎么证明它稳定”。我的回答不是只说“我自己点过很多次”，而是给出明确的测试模块、用例数量和质量门禁。
-->
