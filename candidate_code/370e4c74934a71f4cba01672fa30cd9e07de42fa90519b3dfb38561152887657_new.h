// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73712021;
  double density_weight = 0.07370783;
  double prefix_weight = 0.12836508;
  double neighborhood_weight = 0.31169377;
  double late_weight = 0.15962579;
  double critical_weight = 0.04113634;
  unsigned budget = 16;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
