---
layout: default
transition: slide-left
---

# 改进方向

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div style="display:grid;grid-template-columns:1fr 1fr;gap:1.5rem;">

<div>

<div style="font-weight:600;font-size:0.9rem;margin-bottom:0.75rem;color:#2d7ff9;">近期</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:4px;padding:0.6rem 0.8rem;margin-bottom:0.5rem;font-size:0.85rem;">
<strong>完整 Undo/Redo</strong><br>
<span class="dim" style="font-size:0.75rem;">QUndoStack + QUndoCommand，多级撤销功能</span>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:4px;padding:0.6rem 0.8rem;margin-bottom:0.5rem;font-size:0.85rem;">
<strong>CanvasView 拆分</strong><br>
<span class="dim" style="font-size:0.75rem;">提取 SelectionManager、TransformManager</span>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:4px;padding:0.6rem 0.8rem;margin-bottom:0.5rem;font-size:0.85rem;">
<strong>更多图形类型</strong><br>
<span class="dim" style="font-size:0.75rem;">贝塞尔曲线、星形、文本输入与编辑</span>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:4px;padding:0.6rem 0.8rem;font-size:0.85rem;">
<strong>图层系统</strong><br>
<span class="dim" style="font-size:0.75rem;">Layer 数据结构 + 图层面板</span>
</div>

</div>

<div>

<div style="font-weight:600;font-size:0.9rem;margin-bottom:0.75rem;color:#2d7ff9;">远期</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:4px;padding:0.6rem 0.8rem;margin-bottom:0.5rem;font-size:0.85rem;">
<strong>插件系统</strong><br>
<span class="dim" style="font-size:0.75rem;">IShapePlugin + QPluginLoader 动态加载</span>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:4px;padding:0.6rem 0.8rem;margin-bottom:0.5rem;font-size:0.85rem;">
<strong>SVG 原生导入/导出</strong><br>
<span class="dim" style="font-size:0.75rem;">QSvgRenderer / QSvgGenerator 格式转换</span>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:4px;padding:0.6rem 0.8rem;margin-bottom:0.5rem;font-size:0.85rem;">
<strong>性能优化</strong><br>
<span class="dim" style="font-size:0.75rem;">BSP 树索引、LOD、OpenGL 加速</span>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:4px;padding:0.6rem 0.8rem;font-size:0.85rem;">
<strong>触摸手势</strong><br>
<span class="dim" style="font-size:0.75rem;">Qt PinchGesture 双指缩放旋转</span>
</div>

</div>

</div>

<!--
改进方向分近远期。近期最高优先级是完整的Undo/Redo——当前单级Esc取消只能回退正在进行的操作，多级撤销需要引入QUndoStack框架。其次是重构CanvasView——当前约900行逻辑分布在3个cpp文件中。增加图形类型理论上需要修改7个文件。远期来看，插件系统可以让第三方扩展图形类型，SVG格式支持增强互操作性，性能优化应对大量图形场景，触摸手势适配更多设备。
-->
