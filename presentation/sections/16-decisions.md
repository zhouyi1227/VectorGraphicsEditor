---
layout: default
transition: slide-left
---

# 测试与质量保障

<style>
.metric-strip { gap: 0.5rem; margin-bottom: 0.8rem !important; }
.metric-value { font-size: 1.7rem; }
.metric { padding-top: 0.45rem; }
.metric-label { font-size: 0.78rem; }
.metric-note { font-size: 0.66rem; }
.split-even { gap: 0.7rem; }
.rail-copy { font-size: 0.78rem; line-height: 1.4; }
.rail-title { font-size: 0.88rem; }
.rail-list { gap: 0.45rem; }
.rail-item { padding-left: 0.7rem; }
.deck-stage { padding: 0.7rem 0.95rem; }
</style>

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
        <div class="rail-copy">覆盖序列化往返、版本校验、非法图形、重复 ID、transform 合法性。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>CanvasGeometryTests</code></div>
        <div class="rail-copy">覆盖正交化、等比缩放、防翻转、frame-to-frame 角点映射。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>ShapeItemTests</code> + <code>MainWindowTests</code></div>
        <div class="rail-copy">覆盖路径构建、命中区域、preview 行为、Tools 菜单分组回归。</div>
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
      <div class="rail-copy">检查 bugprone、analyzer、modernize、performance 类问题。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">门禁 3</div>
      <div class="rail-title"><code>ctest --output-on-failure</code></div>
      <div class="rail-copy">用自动化回归替代手动点击测试，失败时直接打印现场。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页我讲质量保障的可验证证据。数字：5 个测试模块、40 个测试函数、2 项静态检查、3 套跨平台 preset。ShapeDataTests 覆盖序列化往返、版本校验、非法图形、重复 ID、transform 合法性。FileManagerTests 和 ShapeDataTests 走同一套 JSON 字段契约。CanvasGeometryTests 覆盖正交化、等比缩放、防翻转、frame-to-frame 角点映射——这些是 core 层的纯函数，可以在没有 QApplication 的进程里跑。ShapeItemTests 覆盖路径构建、命中区域、preview 行为。MainWindowTests 覆盖 Tools 菜单 1 / 3 / 4 分组回归。质量门禁方面：clang-format --dry-run --Werror 是格式门禁，clang-tidy 是静态分析，ctest --output-on-failure 是回归门禁。三个门禁串成一条 CI 链。
-->
