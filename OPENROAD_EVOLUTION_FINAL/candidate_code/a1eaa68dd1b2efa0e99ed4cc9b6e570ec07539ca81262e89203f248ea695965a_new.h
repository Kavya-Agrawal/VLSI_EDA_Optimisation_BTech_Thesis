// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03394156;
  double density_weight = 0.31711175;
  double prefix_weight = 0.36133307;
  double neighborhood_weight = 0.23965719;
  double late_weight = 0.06849803;
  double critical_weight = 0.24686751;
  unsigned budget = 6;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
