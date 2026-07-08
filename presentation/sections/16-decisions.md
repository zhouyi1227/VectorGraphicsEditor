---
layout: default
transition: slide-left
---

# 测试与质量保障

<div class="deck-rule"></div>

<div class="metric-strip mb-5">
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
    <div class="metric-label">跨平台 preset</div>
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
        <div class="rail-copy">序列化往返、版本校验、非法图形、重复 ID、transform 合法性。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>CanvasGeometryTests</code></div>
        <div class="rail-copy">正交化、等比缩放、防翻转、frame-to-frame 角点映射。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>ShapeItemTests</code> + <code>MainWindowTests</code></div>
        <div class="rail-copy">路径构建、命中区域、preview、Tools 菜单分组回归。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">门禁 1</div>
      <div class="rail-title"><code>clang-format --dry-run --Werror</code></div>
      <div class="rail-copy">保证风格一致，避免重构引入格式漂移。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">门禁 2</div>
      <div class="rail-title"><code>clang-tidy</code></div>
      <div class="rail-copy">检查 bugprone、analyzer、modernize 类问题。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">门禁 3</div>
      <div class="rail-title"><code>ctest --output-on-failure</code></div>
      <div class="rail-copy">自动化回归替代手动点击测试。</div>
    </div>
  </div>
</div>

<!--
各位老师，数字：5 个测试模块、40 个测试函数、2 项静态检查、3 套跨平台 preset。质量门禁三件套：clang-format、clang-tidy、ctest。串成一条 CI 链。
-->
